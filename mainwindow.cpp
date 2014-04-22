#include "mainwindow.h"
#include "civ_functions.h"
#include "optionbox.h"
#include "ui_mainwindow.h"
#include "ui_installBox.h"
#include "ui_optionBox.h"

#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtGui>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setWindowTitle("Civilization IV: A New Dawn 2");
    setStyleSheet("MainWindow { background-image: url(checker/and2_background.jpg) }");

    // Check SVN update in background
    if(svnLocalInfo() < svnDistantInfo()) {
        ui->bt_update->setStyleSheet("background-color: yellow");
        ui->bt_update->setText("Update available !");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

installBox::installBox(QDialog *parent) :
  QDialog(parent),
  ui(new Ui::installBox)
{
    ui->setupUi(this);
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
    checkUpdate();
    QMessageBox::information(this, "Information", "The mod is up-to-date.");
}

void installBox::on_buttonBox_accepted()
{
    system("checker\\svn.exe checkout svn://svn.code.sf.net/p/anewdawn/code/Trunk/Rise of Mankind - A New Dawn .  && taskkill /f /im and2_checker.exe >NUL 2>NUL && echo The mod has been installed. && TIMEOUT 3 && start and2_checker.exe");
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
    optionBox *optBox = new optionBox;
    optBox->show();
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
