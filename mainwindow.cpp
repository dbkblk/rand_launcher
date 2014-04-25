#include "mainwindow.h"
#include "civ_functions.h"
#include "optionbox.h"
#include "updatebox.h"
#include "updatemanager.h"
#include "ui_mainwindow.h"
#include "ui_installBox.h"
#include "ui_optionBox.h"
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtGui>
#include <QtWidgets>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ubox = new updatebox(this);
    optbox = new optionBox(this);
    updateGUI = new QWidget (this);
    ask_update = new QMessageBox(this);

	this->setWindowTitle("Civilization IV: A New Dawn 2");
    setStyleSheet("MainWindow { background-image: url(checker/and2_background.jpg) }");

    /*  Thread code, imported from https://github.com/fabienpn/simple-qt-thread-example */
    thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(UMCheckLauncherUpdate()));
    connect(worker, SIGNAL(finished(bool)), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished(bool)), this, SLOT(UpdateAvailable(bool)), Qt::DirectConnection);

    // Check launcher update in background (to avoid having two threads running simultaneously, the previous thread is aborted).
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.

    worker->requestWork();

    // Check SVN update in background
    if(svnLocalInfo() < svnDistantInfo()) {
        ui->bt_update->setStyleSheet("background-color: yellow");
        ui->bt_update->setText("Update available !");
    }

    // Versions label
    QString vers = "Mod rev. " + readCheckerParam("MAIN/LocalRev") + " - Launcher rev. " + readCheckerParam("MAIN/CheckerVersion");
    QPalette lb_palette;
    lb_palette.setColor(QPalette::WindowText, Qt::white);
    //ui->lb_versions->setAutoFillBackground(true);
    ui->lb_versions->setPalette(lb_palette);
    ui->lb_versions->setText(vers);

}

MainWindow::~MainWindow()
{
    worker->abort();
    thread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete thread;
    delete worker;
    delete ui;
}

void MainWindow::UpdateAvailable(bool update)
{
    qDebug() << "Update argument is" << update;
    if(update)
    {
        qDebug() << "Entering update loop";
        ask_update->setWindowTitle("Launcher update available");
        ask_update->setText("An update of the launcher is available.");
        ask_update->setInformativeText("Do you want to update ?");
        ask_update->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = ask_update->exec();
        switch (ret) {
            case QMessageBox::Ok :
                launcherUpdate();
                break;

            case QMessageBox::Cancel :
                break;
        }
    }
}

installBox::installBox(QDialog *parent) :
  QDialog(parent),
  ui(new Ui::installBox)
{
    ui->setupUi(this);
    inst_view = new updatebox(this);
}

// Menu actions

void MainWindow::on_actionForum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/forumdisplay.php?f=369"));
}

void MainWindow::on_actionAddon_Mega_Civ_Pack_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=521289"));
}

void MainWindow::on_actionBugreport_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=474185"));
}

void MainWindow::on_actionAbout_AND_Resurrection_team_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=471460"));
}

void MainWindow::on_actionAddon_More_music_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=523763"));
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// Menu buttons

void MainWindow::on_bt_update_clicked()
{
    // Calculate changelog difference
    int chglog_diff = readCheckerParam("MAIN/DistantRev").toInt() - readCheckerParam("MAIN/LocalRev").toInt();
    qDebug() << "The changelog diff is equal to " << chglog_diff;

    if(chglog_diff == 0) {
        QMessageBox::information(this, "Information", "There is no update at the moment.");
    }
    else if(chglog_diff >= 1) {
        bool value = true;
        char command[30];
        sprintf(command,"checker/svn.exe log -l %d -r HEAD:BASE",chglog_diff);
        ubox->show();
        ubox->setWindowTitle("Update tool");
        ubox->execute(command,value);
    }
    else
        QMessageBox::critical(this, "Error", "An error has occured while checking for updates.");
}

void installBox::on_buttonBox_accepted()
{
    inst_view->show();
    inst_view->updateMode();
    inst_view->setWindowTitle("Downloading mod...");
    bool cursor = false;
    inst_view->execute("checker/svn.exe checkout \"svn://svn.code.sf.net/p/anewdawn/code/Trunk/Rise of Mankind - A New Dawn\" .", cursor);
    inst_view->bt_chglog_close->show();
    connect(inst_view->bt_chglog_close,SIGNAL(clicked()),inst_view,SLOT(close()));
}

void installBox::on_buttonBox_rejected()
{
    qApp->exit();
}

void MainWindow::on_bt_launch_clicked()
{
    // Check if the game path is known
    if(readCheckerParam("MAIN/ExecutablePath") == NULL) {
        QMessageBox::information(0, "Information", "To be able to launch the game from the launcher, you need to set the game path in the options window. (Options > Select game path)");
        return;
    }
    else {
        launchGame();
    }

    // Check if the launcher should quit
    if(readCheckerParam("MAIN/QuitLauncher") == "1") {
        qApp->exit();
    }
    else {
        this->setWindowState(Qt::WindowMinimized);
    }
}

void MainWindow::on_bt_option_clicked()
{
    optbox->show();
}

Downloader::Downloader(void)
{
    manager = new QNetworkAccessManager;
}

Downloader::~Downloader(void)
{
}

QString Downloader::download(QString in_url, QString in_output)
{
    QUrl url(in_url);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));

    // Event loop to wait for the download to finish
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if(reply->error() == QNetworkReply::NoError)
    {
        replyFinished(reply, in_output);
        return "ok";
    }
    else
    {
        return reply->errorString();
    }
}

void Downloader::replyFinished(QNetworkReply* r, QString in_output)
{
    QFile url_file(in_output);
    url_file.open(QIODevice::WriteOnly);
    url_file.write(r->readAll());
    url_file.close();
    qDebug() << "Downloader replied";
}

void MainWindow::on_pushButton_clicked()
{
    // Preparing for update
    QDir temp;
    temp.mkdir("temp");
    QFile::copy("checker/upd_proc.exe","temp/upd_proc.exe");
    QFile::copy("checker/7za.exe","temp/7za.exe");
    QFile::copy("checker/wget.exe","temp/wget.exe");
    QFile::copy("icudt51.dll","temp/icudt51.dll");
    QFile::copy("icuin51.dll","temp/icuin51.dll");
    QFile::copy("icuuc51.dll","temp/icuuc51.dll");
    QFile::copy("libgcc_s_dw2-1.dll","temp/libgcc_s_dw2-1.dll");
    QFile::copy("libstdc++-6.dll","temp/libstdc++-6.dll");
    QFile::copy("libwinpthread-1.dll","temp/libwinpthread-1.dll");
    QFile::copy("Qt5Core.dll","temp/Qt5Core.dll");
    QFile::copy("Qt5Gui.dll","temp/Qt5Gui.dll");
    QFile::copy("Qt5Widgets.dll","temp/Qt5Widgets.dll");
    QProcess::startDetached("temp/upd_proc.exe");
}
