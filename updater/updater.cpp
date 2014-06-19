#include "updater.h"
#include "QLabel"
#include "QCoreApplication"
#include <QApplication>
#include <QDesktopWidget>
#include "QProcess"
#include "QFile"
#include <QDir>
#include <QSettings>
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>

updater::updater(QWidget *parent)
    : QMainWindow(parent)
{

    central->setText(tr("Killing existing process..."));
    this->setCentralWidget(central);

    // Layout definition
    this->setFixedHeight(50);
    this->setFixedWidth(150);
    this->setContentsMargins(15,15,15,15);
    this->setWindowTitle("Updater");
    this->central->setGeometry(20,20,125,30);
    this->show();
}

updater::~updater()
{
    qApp->exit();
}

void updater::exit()
{
    qApp->exit();
}

void updater::Execute(QString link)
{
    // Loops
    QTimer wait_timer;
    QEventLoop wait_install;
    wait_timer.setInterval(1000);
    wait_timer.setSingleShot(true);
    connect(&wait_timer,SIGNAL(timeout()),&wait_install,SLOT(quit()));
    connect(proc,SIGNAL(finished()),&wait_install,SLOT(quit()));

    proc->KillProcess();
    wait_timer.start();
    central->setText(tr("Downloading update..."));
    wait_install.exec();
    proc->Download(link);
    wait_timer.start();
    central->setText(tr("Extracting update..."));
    wait_install.exec();
    proc->Extraction();
    wait_timer.start();
    central->setText(tr("Finalization..."));
    wait_install.exec();
    proc->Finalization();

    delete this;
}

void process::KillProcess()
{
    tasks->start("taskkill /f /im and2_checker.exe");
    emit finished();
}

void process::Download(QString link)
{
    qDebug() << link;
    QString command = "checker/curl.exe -o AND2_CHECKER_UPDATE.7z -J -L -C - -# --retry 10 --insecure " + link;
    tasks->execute(command);
    emit finished();
}

void process::Extraction()
{
    QFile::copy("checker/7za.exe","7za.exe");
    QString command = "7za.exe x -y AND2_CHECKER_UPDATE.7z";
    tasks->execute(command);
    emit finished();
}

void process::Finalization()
{
    QFile::remove("7za.exe");
    QFile::remove("AND2_CHECKER_UPDATE.7z");
    QFile::remove("checker/update.ini");
    tasks->startDetached("and2_checker.exe");
    emit finished();
}

