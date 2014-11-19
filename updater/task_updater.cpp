#include "task_updater.h"
#include "ui_task_updater.h"
#include <QtCore>
#include <QtXml/QtXml>
#include <QMessageBox>
#include <QApplication>

task_updater::task_updater(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::task_updater)
{
    // Setting GUI and process
    ui->setupUi(this);
    ui->label->setText(tr("Updating the game. Please be patient."));
    process = new QProcess(this);
    ui->progressBar->setRange(0,100);

    // Disable debug output

    // Connecting signals
    connect(this,SIGNAL(finished()),this,SLOT(restartLauncher()));
    connect(this,SIGNAL(stopUpdate()),this,SLOT(StopGUI()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    connect(this,SIGNAL(error()),this,SLOT(errorPopup()));
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

void task_updater::StartUpdate(QString operation){
    // Set process and emit signal at the end
    process->start(operation);
    process->waitForFinished(-1);
    emit finished();
}

void task_updater::processOutput(){
    // Get standard output
    QString output = process->readAllStandardOutput();
    qDebug() << output;

    // Check for errors
    if(output.contains("error")){emit error();}

    // Extract percent
    //      75,634,656   2%   10.23MB/s    0:00:07 (xfr#77, to-chk=0/13260)
    int pos = 0;
    int bracket = 0;
    int separator = 0;
    int value;
    int total;
    int percent = 0;
    if (output.contains("to-chk=")){
        pos = output.lastIndexOf("to-chk=");
        separator = output.lastIndexOf("/");
        bracket = output.lastIndexOf(")");
        value = output.mid((pos+7),(separator-(pos+7))).toInt();
        qDebug() << "Files to check: " << value;
        total = output.mid((separator+1),(bracket-(separator+1))).toInt();
        //qDebug() << total;
        // Avoid crash on windows
        if (total >  0){
            percent = ((total - value)*100 / total);
        }

        // Update progress bar
        ui->progressBar->setValue(percent);

        // Update label
        QString label = QString(tr("Checking and downloading data: ")) + QString::number(value) + QString(tr(" files left."));
        //qDebug() << label;
        ui->label->setText(label);
        ui->label->repaint();
        if(percent == 100){emit stopUpdate();}
    }
    QCoreApplication::processEvents();
}

void task_updater::errorPopup()
{
    qDebug("An error has occured");
}

void task_updater::StopGUI()
{
    disconnect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    QFile::remove("updating");
}

void task_updater::restartLauncher()
{
    QProcess::startDetached(tools::TOOL_LAUNCHER);
}

QString task_updater::ReadExcludeList(QString filepath){
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
            exclude_list = exclude_list + "--exclude \"" + entry + "\" ";
        }
    }
    //qDebug() << exclude_list;

    return exclude_list;
}
