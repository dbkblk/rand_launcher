#include "w_main.h"
#include "f_updater.h"
#include "ui_w_main.h"
#include <QtCore>
#include <QMessageBox>
#include <QApplication>

w_main::w_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::w_main)
{
    ui->setupUi(this);

    // Translations : Get language parameter, else if OS language, then wait to fully initialize the GUI.
    translator = new QTranslator(this);
    QString loc;
    if(readCheckerParam("Main/Lang") == "error")
    {
        loc = QLocale::system().name().section('_', 0, 0);
    }
    else
    {
        loc = readCheckerParam("Main/Lang");
    }
    qDebug() << "Language used: " << loc;
    translator->load(QString("launcher_" + loc + ".qm"),"checker/lang/");

    qApp->installTranslator(translator);

    // Setting GUI and process
    ui->label->setText(tr("Updating the game. Please be patient."));
    ui->progressBar->setRange(0,100);

    // Prepare thread
    //qDebug("Prepare thread");
    thread = new QThread();
    worker = new f_updater();
    worker->moveToThread(thread);
    connect(worker,SIGNAL(workRequested()), thread, SLOT(start()));
    connect(worker,SIGNAL(finished()),this,SLOT(restartLauncher()));
    connect(worker,SIGNAL(error()),this,SLOT(errorPopup()));
    connect(worker,SIGNAL(progress(int, int)),this,SLOT(updateInterface(int,int)));
    //qDebug("Connected signals");
    ui->retranslateUi(this);
}

w_main::~w_main()
{
    //qDebug("Kill UI");
    worker->abort();
    thread->wait();
    delete thread;
    delete worker;
    delete ui;
}

void w_main::ResetInstallation(){
    connect(thread, SIGNAL(started()), worker, SLOT(resetLaunch()));

    // Kill previous and request work
    worker->abort();
    thread->wait();
    worker->requestWork();
}

void w_main::DebugWindow(int time)
{
    // GUI: Fix the interface lockup
    QTimer wait_timer;
    QEventLoop wait_install;
    wait_timer.setInterval(time);
    wait_timer.setSingleShot(true);
    connect(&wait_timer,SIGNAL(timeout()),&wait_install,SLOT(quit()));
    wait_timer.start();
    wait_install.exec();
}

void w_main::StartUpdate(){
    connect(thread, SIGNAL(started()), worker, SLOT(updateLaunch()));

    // Kill previous and request work
    worker->abort();
    thread->wait();
    worker->requestWork();
}

void w_main::updateInterface(int percent, int value){
    ui->progressBar->setValue(percent);
    QString label = QString(tr("Checking and downloading data:")+" ") + QString::number(value) + QString(" " + tr(" files left."));
    //qDebug() << label;
    ui->label->setText(label);
    //ui->label->repaint();
}

void w_main::errorPopup()
{
    qDebug("An error has occured");
}

void w_main::restartLauncher()
{
    //qDebug("Restart launcher");
    QFile::remove("updating");
    QProcess::startDetached(tools::TOOL_LAUNCHER);
    this->close();
}

QString w_main::readCheckerParam(QString param)
{
    QSettings settings("checker/checker_config.ini", QSettings::IniFormat);
    if(!settings.contains(param)) {
        return "error";
    }
    QString value = settings.value(param).toString();
    return value;
}

