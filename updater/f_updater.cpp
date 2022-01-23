#include "f_updater.h"
#include "QtCore"
#include "w_main.h"
#include <QtXml>



f_updater::f_updater(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
    process = new QProcess(this);
    // Connecting signals
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
}

void f_updater::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug("Starting update process...");
    mutex.unlock();

    emit workRequested();
}

void f_updater::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<  "Request worker aborting in Thread " <<   thread()->currentThreadId();
    }
    mutex.unlock();
}

void f_updater::updateLaunch(){
    // Write temp file
    QFile temp("updating");
    temp.open(QIODevice::WriteOnly | QIODevice::Truncate);
    temp.close();

    // Prepare update
    QString exclusion_default = readExcludeList("checker/exclusions.default.xml");
    QString exclusion_custom = readExcludeList("checker/exclusions.custom.xml");
    QString exclusion_mods = readExcludeList("checker/exclusions.mods.xml");
    QString operation = tools::TOOL_RSYNC + QString("-rz --force --progress --delete-after %1%2%3rsync://afforess.com/ftp/ .").arg(exclusion_default).arg(exclusion_custom).arg(exclusion_mods);
    qDebug() << operation;

    // Set process and emit signal at the end
    process->start(operation);
    process->waitForFinished(-1);

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    emit finished();
}

void f_updater::resetLaunch(){
    // Prepare process
    QFile temp("reset");
    temp.open(QIODevice::WriteOnly | QIODevice::Truncate);
    temp.close();
    QString operation = tools::TOOL_RSYNC + QString("-rz --force --progress --delete-after --exclude=\".svn*\" --exclude=\"updating\" afforess.com::ftp/ .");
    qDebug() << operation;

    // Set process and emit signal at the end
    process->start(operation);
    //process->execute(operation); //Uncomment execute to debug
    process->waitForFinished(-1);

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();
}

void f_updater::processOutput(){

    // Get standard output
    QString output = process->readAllStandardOutput();
    QRegExp regex ("to-chk=(\\d*)\\/(\\d*)");
    //qDebug() << output;

    // Check for errors
    if(output.contains("error")){emit error();}

    // Extract percent
    //      75,634,656   2%   10.23MB/s    0:00:07 (xfr#77, to-chk=0/13260)
//    int pos = 0;
//    int bracket = 0;
//    int separator = 0;
    int value;
    int total;
    int percent = 0;
    if (output.contains(regex)){
        // Formal detection
//        pos = output.lastIndexOf("to-chk=");
//        separator = output.lastIndexOf("/");
//        bracket = output.lastIndexOf(")");
//        value = output.mid((pos+9),(separator-(pos+9))).toInt();
//        qDebug() << "Files to check: " << value;
//        total = output.mid((separator+1),(bracket-(separator+1))).toInt();

        // Regex detection
        value = regex.cap(1).toInt();
        total = regex.cap(2).toInt();
        //qDebug() << total;
        // Avoid crash on windows
        if (total >  0){
            percent = ((total - value)*100 / total);

            // Emit update signal
            emit progress(percent, value);
        }
    }
}

QString f_updater::readExcludeList(QString filepath){
    // Read an XML subfolder (checker/exclusions/exclusions.xml) to be able to add individual addons xml later

    QString exclude_list;
    // Open the XML file
    QDomDocument read;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening file";
         return 0;
     }
    read.setContent(&file);
    file.close();

    // Read every exclusions
    QStringList exclusions;
    QDomElement entity = read.firstChildElement("exclusions").firstChildElement();

    while(!entity.isNull()){
        exclusions << entity.text();
        //qDebug() << entity.text();
        entity=entity.nextSiblingElement();
    }

    // Split string list into a formatted exclusion list
    foreach(QString entry, exclusions){
        if(!entry.isEmpty()){
            exclude_list = exclude_list + "--exclude=\"" + entry + "\" ";
        }
    }
    //qDebug() << exclude_list;

    return exclude_list;
}

