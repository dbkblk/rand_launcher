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
    QProcess::execute("taskkill /f /im svn.exe");
    delete ui;
}

QString task_updater::svn_update(int current_revision, int output_revision)
{
    // Clean up before initialization
    QProcess clean;
    clean.start("checker/svn.exe cleanup");
    clean.waitForFinished(-1);
    clean.start("checker/svn.exe revert and2_checker.exe");
    clean.waitForFinished(-1);
    clean.start("checker/svn.exe revert -R checker/");
    clean.waitForFinished(-1);

    // Begin updater process
    initialize();
    QString head;
    if(output_revision > 0)
    {
        head = QString::number(output_revision);
    }
    else
    {
        head = "HEAD";
    }
    // Set interface unlocker
    QTimer wait_timer;
    QEventLoop wait_install;
    wait_timer.setInterval(1000);
    wait_timer.setSingleShot(true);
    connect(&wait_timer,SIGNAL(timeout()),&wait_install,SLOT(quit()));
    wait_timer.start();
    wait_install.exec();

    // Get number of files
    QProcess svn;
    svn.setStandardOutputFile("svn_files");
    svn.start(QString("checker/svn.exe log -qv -r %1:%2 --xml").arg(current_revision).arg(head));
    svn.waitForFinished(-1);
    //qDebug() << "Finished";
    QFile svn_out("svn_files");
    int counter = 0;

    QStringList file_list;
    QString file_value;
    if(svn_out.open(QFile::ReadOnly))
    {
        QDomDocument xml;
        xml.setContent(&svn_out);
        QDomElement logentry = xml.firstChildElement("log").firstChildElement("logentry");
        for(logentry;!logentry.isNull();logentry = logentry.nextSiblingElement())
        {
            QDomElement file_entry = logentry.firstChildElement("paths").firstChildElement("path");
            for(file_entry;!file_entry.isNull();file_entry = file_entry.nextSiblingElement())
            {
                file_value = file_entry.firstChild().nodeValue();
                if(!file_entry.attribute("action").isNull())
                {
                    if(file_value.contains("/Trunk/Rise of Mankind - A New Dawn/"))
                    {
                        file_list << file_value;
                    }
                }
            }
        }

        file_list.removeDuplicates();
        counter = file_list.count();
    }
    qDebug() << "Counted" << counter << "lines";
    svn_out.close();
    svn_out.remove();

    // Set progress bar
    ui->progressBar->setRange(0,counter);

    QString behavior = "tf";
    behavior = readCheckerParam("Main/UpdateBehavior");
    qDebug() << "Update behavior is set to " << behavior;

    if(output_revision > 0)
    {
        execute(QString("checker/svn.exe update -r %1 --non-interactive --accept %2").arg(output_revision).arg(behavior));
    }
    else{
        execute(QString("checker/svn.exe update --non-interactive --accept %1").arg(behavior));
    }


    return "temp";
}

void task_updater::initialize()
{
    // Process
    process_file = QString("tmp_file.txt");
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setStandardOutputFile(process_file);
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(executeFinished()));
    connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(executeError(QProcess::ProcessError)));
    process_timer.setInterval(500);
    process_timer.setSingleShot(false);
    connect(&process_timer, SIGNAL(timeout()), this, SLOT(appendOutput()));
    progress = -1;
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
        QString text = file.readLine();
        ui->console_output->insertPlainText(text);
        ui->console_output->moveCursor(QTextCursor::End);
        if(text.startsWith("A ") || text.startsWith("U ") )
        {
            progress++;
            ui->progressBar->setValue(progress);
        }
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

void task_updater::appendText(QString text)
{
    ui->console_output->append(text);
    ui->console_output->moveCursor(QTextCursor::End);
}

void task_updater::restartLauncher()
{
    QProcess::startDetached("and2_checker.exe");
    QApplication::quit();
}

void task_updater::addonInstaller(QString name, QString link)
{

}

void task_updater::svn_install()
{
    ui->label->setText(tr("Please be patient during the installation:"));
    initialize();
    ui->progressBar->hide();
    execute("checker/svn.exe checkout \"svn://svn.code.sf.net/p/anewdawn/code/Trunk/Rise of Mankind - A New Dawn\" .");
}

QString readCheckerParam(QString param)
{
    QSettings settings("checker/checker_config.ini", QSettings::IniFormat);
    if(!settings.contains(param)) {
        return "error";
    }
    QString value = settings.value(param).toString();
    return value;
}
