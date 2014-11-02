#include "task_updater.h"
#include "ui_task_updater.h"
#include <QtCore>
#include <QtXml/QtXml>
#include <QMessageBox>

task_updater::task_updater(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::task_updater)
{
    ui->setupUi(this);
    ui->label->setText(tr("Updating the game:"));

    connect(this,SIGNAL(finished()),this,SLOT(restartLauncher()));
}

task_updater::~task_updater()
{
    delete ui;
}

void task_updater::DebugWindow()
{
    // GUI: Fix the interface lockup
    QTimer wait_timer;
    QEventLoop wait_install;
    wait_timer.setInterval(0500);
    wait_timer.setSingleShot(true);
    connect(&wait_timer,SIGNAL(timeout()),&wait_install,SLOT(quit()));
    wait_timer.start();
    wait_install.exec();
}

int task_updater::CountFiles()
{
    // Rsync to get file list
    QProcess rsync;
    QFile::remove("temp");
    QString operation = tools::TOOL_RSYNC + "-qr --stats --log-file=temp --exclude=\".svn*\" afforess.com::ftp/ .";
    qDebug() << "Checking server for updates: " << operation;
    rsync.execute(operation);

    // TO REVIEW (extract from stats) Count lines numbers
    QFile file("temp");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_enc(&file);
    int counter = 0;
    while(!in_enc.atEnd())
    {
        QString line = in_enc.readLine();
        QString files;
        if(line.contains("Number of files:")){
            // Get file numbers
            int pos = line.lastIndexOf("Number of files:");
            pos = pos + 17;
            for(pos;pos < 60;pos++){
                QChar ch = line.at(pos);
                if(ch.isSpace()){
                    pos = 60;
                }
                else {
                    //qDebug() << ch;
                    files += ch;
                }
            }
            counter = files.replace(",","").toInt();

            // Remove dir numbers
            pos = line.lastIndexOf("dir:");
            pos = pos + 5;
            files = "";
            for(pos;pos < 100;pos++){
                QChar ch = line.at(pos);
                if(!ch.isDigit()){
                    pos = 100;
                }
                else {
                    //qDebug() << ch;
                    files += ch;
                }
            }
            counter = counter - files.replace(",","").toInt() + 6;
            //qDebug() << files;

        }
        if(line.contains("rsync error")){
            return -1;
        }

    }
    file.close();

    //qDebug() << "Counted" << counter << "files";
    QFile::remove("temp");
    ui->progressBar->setRange(0,counter);
    qDebug() << counter << "files to check.";
    return counter;
}

void task_updater::initialize()
{
    // Process initialization (invoke before execute)
    process_file = QString("temp_rsync");
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setStandardOutputFile(process_file);
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(executeFinished()));
    connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(executeError(QProcess::ProcessError)));
    process_timer.setInterval(500);
    process_timer.setSingleShot(false);
    connect(&process_timer, SIGNAL(timeout()), this, SLOT(appendOutput()));
    progress = 0;
}

void task_updater::execute(QString command)
{
    QFile::remove(process_file);
    process_file_pos = 0;
    process.start(command);
    process_timer.start();
}

void task_updater::appendOutput()
{
  QFile file(process_file);
  if (!file.open(QIODevice::ReadOnly)) return;

  // Move cursor
  if (file.size()>process_file_pos)
  {
    file.seek(process_file_pos);
    while(!file.atEnd())
    {
        file.readLine();
        progress++;
        //qDebug() << progress;
        ui->progressBar->setValue(progress);
    }
    process_file_pos = file.pos();
  }
  file.close();
}

void task_updater::executeFinished()
{
  process_timer.stop();
  appendOutput();
  QFile::remove("checker/updater.log");
  QFile::copy(process_file,"checker/updater.log");
  QFile::remove(process_file);

  emit finished();
}

void task_updater::executeError(QProcess::ProcessError)
{
    process_timer.stop();
    appendOutput();
    QFile::remove(process_file);
}

void task_updater::restartLauncher()
{
    QProcess::startDetached(tools::TOOL_LAUNCHER);
    QApplication::quit();
}

QString task_updater::ReadExcludeList(){
    // Read an XML subfolder (checker/exclusions/exclusions.xml) to be able to add individual addons xml later

    QString exclude_list;
    // Open the XML file
    QDomDocument read;
    QFile file("checker/exclusions.default.xml");
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
            exclude_list = exclude_list + "--exclude \"" + entry + "\" ";
        }
    }
    //qDebug() << exclude_list;

    return exclude_list;
}
