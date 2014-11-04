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
    ui->label->setText(tr("Updating the game:"));
    process = new QProcess(this);
    ui->progressBar->setRange(0,100);

    // Disable debug output

    // Connecting signals
    connect(this,SIGNAL(finished()),this,SLOT(restartLauncher()));
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

    // Check for errors
    if(output.contains("error")){emit error();}

    // Extract percent
    //      75,634,656   2%   10.23MB/s    0:00:07 (xfr#77, to-chk=0/13260)
    int pos = 0;
    int bracket = 0;
    int i=0;
    int value;
    int total;
    if (output.contains("to-chk=")){
        pos = output.lastIndexOf("to-chk=");
        bracket = output.lastIndexOf(")");
        QString string = output.mid((pos+8),(pos+8-bracket));
        QStringList list = string.split("/");
        foreach(QString number, list){
            number.replace(")","");
            if(i==0){
                value = number.toInt();
            }
            if(i==1){
                total = number.toInt();
            }
            i++;
        }
        int percent = ((total - value)*100 / total);
        ui->progressBar->setValue(percent);
    }

    // Extract speed
    pos = output.indexOf("/s");
    QString ext_speed;
    ext_speed.append(output.at(pos-10)).append(output.at(pos-9)).append(output.at(pos-8)).append(output.at(pos-7)).append(output.at(pos-6));
    int speed = ext_speed.toInt();
    if(QChar(output.at(pos-2)) == QString("M")){speed = speed * 1000;};

    // Extract time left
    int hours;
    int minutes;
    int seconds;
    QString ext_time;
    pos = output.indexOf(":");
    hours = ext_time.append(output.at(pos-2)).append(output.at(pos-1)).toInt();
    ext_time = "";
    minutes = ext_time.append(output.at(pos+1)).append(output.at(pos+2)).toInt();
    ext_time = "";
    seconds = ext_time.append(output.at(pos+4)).append(output.at(pos+5)).toInt();

    QString time_left;
    if(hours != 0){time_left.append(QString::number(hours) + "h");}
    if(minutes != 0){time_left.append(QString::number(minutes) + "m");}
    if(seconds != 0){time_left.append(QString::number(seconds) + "s");}
    if(hours != 0 || minutes != 0 || seconds != 0){time_left.append(" " + tr("left")).prepend(" ").prepend(",");}

    //qDebug() << time_left;

    // Update label
    QString label = QString(tr("Updating the game: ")) + QString::number(speed) + QString("kB/s") + time_left;
    //qDebug() << label;
    ui->label->setText(label);
}

void task_updater::errorPopup()
{
    qDebug("An error has occured");
}

void task_updater::restartLauncher()
{
    QProcess::startDetached(tools::TOOL_LAUNCHER);
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
