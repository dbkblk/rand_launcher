#include "updatemanager.h"
#include "ui_updatemanager.h"
#include "civ_functions.h"

#include "QObject"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QFile>

updateManager::updateManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updateManager)
{
    ui->setupUi(this);
}

updateManager::~updateManager()
{
    delete ui;
}

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Worker::UMCheckLauncherUpdate()
{
    // Wait 5s before to check for update
    QEventLoop loop;
    QTimer::singleShot(10000, &loop, SLOT(quit()));
    loop.exec();

    // Begin processing
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();
    bool update;
    QProcess download;
    download.start("checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://raw.githubusercontent.com/dbkblk/and2_checker/master/update.ini");

    if (download.waitForFinished(60000))
    {
        QSettings upd_ini("update.ini", QSettings::IniFormat);
        float loc_version = readCheckerParam("MAIN/CheckerVersion").toFloat();
        float dist_version = upd_ini.value("VERSION/CheckerVersion").toFloat();
        setCheckerParam("MAIN/Changelog",upd_ini.value("VERSION/Changelog").toString());
        qDebug() << "Local version : " << loc_version;
        qDebug() << "Distant version : " << dist_version;
        if(loc_version < dist_version) {
            qDebug() << "An update is available";
            update = true;
            qDebug() << "Update is " << update;
        }
        else
        {
            qDebug() << "No update is required";
            QFile::remove("update.ini");
            update = false;
        }
    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    // Finished signal
    emit finished(update);
}
