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
    //download.start("checker/wget.exe -c -t 10 --retry-connrefused --no-check-certificate --waitretry=10 https://dl.dropboxusercontent.com/u/369241/update.ini");

    if (download.waitForFinished(60000))
    {
        QSettings upd_ini("update.ini", QSettings::IniFormat);
        float loc_version = readCheckerParam("MAIN/CheckerVersion").toFloat();
        float dist_version = upd_ini.value("VERSION/CheckerVersion").toFloat();
        setCheckerParam("MAIN/Changelog",upd_ini.value("VERSION/Changelog").toString());
        setCheckerParam("MAIN/DistantCheckerVersion",upd_ini.value("VERSION/CheckerVersion").toString());
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

bool launcherUpdate()
{
    QSettings upd_ini("update.ini", QSettings::IniFormat);
    QString downloadlink = upd_ini.value("VERSION/DownloadLink").toString();
    QString downloadfile = upd_ini.value("VERSION/DownloadFile").toString();
    qDebug() << "Link : " << downloadlink << endl << "File : " << downloadfile;
    char cmd[512];
    QFile::copy("checker/7za.exe","7za.exe");
    sprintf(cmd, "taskkill /f /im and2_checker.exe && SLEEP 1 && checker\\wget.exe -c --no-check-certificate %s && SLEEP 1 && 7za.exe x -y %s && SLEEP 1 && del 7za.exe && SLEEP 1 && del update.ini && SLEEP 1 && del %s && SLEEP 1 && start and2_checker.exe", downloadlink.toStdString().c_str(), downloadfile.toStdString().c_str(), downloadfile.toStdString().c_str());
    qDebug() << "Update command : " << cmd;
    system(cmd);
    return 0;
}

// Clear the cache folder

bool clearCache()
{
    // Getting the cache path
    std::string cacheDir;
    std::string delCmd = "DEL /Q ";
    std::string quote = "\"";
    std::string finalDir = "\\My Games\\Beyond the Sword\\cache\\";
    std::string dat = "*";
    char* Appdata = getenv("LOCALAPPDATA");
    cacheDir = delCmd + quote + Appdata + finalDir + dat + quote;
    // cout << cacheDir << endl;

    return 0;
}

int svnLocalInfo(){
    // Get the info from the distant server
    QProcess svn_loc;
    svn_loc.setStandardOutputFile("svn.txt");
    svn_loc.start("checker\\svn.exe", QStringList() << "info");
    svn_loc.waitForFinished(-1);

    // Open the output file
    QFile svn_out_loc("svn.txt");
    QString svn;
    QString rev;

    // Find the local revision
    if(svn_out_loc.open(QFile::ReadWrite  |QFile::Text))
    {
        while(!svn_out_loc.atEnd())
        {
            svn += svn_out_loc.readLine();
        }
        int j = 0;
        while ((j = svn.indexOf("Revision: ", j)) != -1) {
             rev = svn.mid(j+10,3);
             ++j;
         }
        qDebug() << "Local revision : " << rev;
    setCheckerParam("MAIN/LocalRev",rev);
    svn_out_loc.close();
    QFile::remove("svn.txt");
    return rev.toInt();
    }

    return 0;
}

int svnDistantInfo()
{
        // Get the info from the distant server
        QProcess svn_dist;
        svn_dist.setStandardOutputFile("svn_dist.txt");
        svn_dist.start("checker\\svn.exe", QStringList() << "info" << "-r" << "HEAD");
        svn_dist.waitForFinished(-1);

        // Open the output file
        QFile svn_out_dist("svn_dist.txt");
        QString svn_str_dist;
        QString rev_dist;

        // Find the local revision
        if(svn_out_dist.open(QFile::ReadWrite  |QFile::Text))
        {
            while(!svn_out_dist.atEnd())
            {
                svn_str_dist += svn_out_dist.readLine();
            }
            int j = 0;
            while ((j = svn_str_dist.indexOf("Revision: ", j)) != -1) {
                 rev_dist = svn_str_dist.mid(j+10,3);
                 ++j;
             }
            qDebug() << "Distant revision : " << rev_dist;
        setCheckerParam("MAIN/DistantRev",rev_dist);
        svn_out_dist.close();
        QFile::remove("svn_dist.txt");
        }
        return rev_dist.toInt();
}


