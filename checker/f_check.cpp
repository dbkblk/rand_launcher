#include "f_civ.h"
#include "w_main.h"

#include "QObject"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QtXml/QtXml>

f_check::f_check(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}

void f_check::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    //qDebug() << "Request worker start in Thread "<<thread()->currentThreadId();
    qDebug("Starting update checking...");
    mutex.unlock();

    emit workRequested();
}

void f_check::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<  "Request worker aborting in Thread " <<   thread()->currentThreadId();
    }
    mutex.unlock();
}

void f_check::CheckForUpdate()
{
    // Wait 3s before to check for update
    QEventLoop loop;
    QTimer::singleShot(3000, &loop, SLOT(quit()));
    loop.exec();

    // Begin processing
    //qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();
    bool update;
    QFile::remove("checker/changelog_last.xml");
    QProcess download;
    QString get_address = tools::TOOL_GET + "-o checker/changelog_last.xml http://civ.afforess.com/changelog_last.xml";
    //qDebug() << get_address;
    download.start(get_address);

    if (download.waitForFinished(60000))
    {
        // Check for update
        if(GetDistantVersion() > GetLocalVersion()){
            update = true;
        }
        else {
            update = false;
        }
        qDebug() << "New version available :" << update;

    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    //qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();
    qDebug("Update checking ended...");
    // Finished signal
    emit finished(update);
}

bool f_check::ActionUpdate()
{
    // Copy the required files (May need to be copied to %TEMP% to avoid to have to clean after ?)

    QFile::copy("checker/upd_proc.exe","upd_proc.exe");
    QFile::copy("checker/rsync.7z","rsync.7z");
    QProcess::execute("checker/7za.exe e rsync.7z");
    QProcess update;
    update.startDetached("upd_proc.exe");

    return 0;
}

int f_check::GetLocalVersion()
{
    //** Get version number from "Assets/Python/Contrib/CvModName.py"
    // Open python file
    QFile file("Assets/Python/Contrib/CvModName.py");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_enc(&file);
    while(!in_enc.atEnd())
    {
        // Go to the mod version
        QString line = in_enc.readLine();
        QString version;
        if(line.contains("modVersion = "))
        {
            version = line.right(5).left(3);
            qDebug() << "Local version : " << version;
            setCheckerParam("Main/LocalRev",version);
            return version.toInt();
        }
    }
    file.close();

    return 0;
}

int f_check::GetDistantVersion()
{
    // Extract the distant version number from the downloaded file
    // Open XML changelog
    QDomDocument read;
    QFile file("checker/changelog_last.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening short changelog";
         return 0;
     }
    read.setContent(&file);
    file.close();

    // Return revision number
    QString version = read.firstChildElement("log").firstChildElement("logentry").attribute("revision");
    qDebug() << "Distant version : " << version;
    return version.toInt();
}
