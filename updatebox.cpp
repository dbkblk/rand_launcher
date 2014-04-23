#include "updatebox.h"
#include "ui_updatebox.h"
#include "mainwindow.h"
#include <QDir>
#include <QFile>
#include <QBoxLayout>
#include <QTextStream>
#include <QDebug>
#include <QPushButton>

updatebox::updatebox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::updatebox)
{
    ui->setupUi(this);

    // Add the close button
    bt_chglog_close = new QPushButton(this);
    bt_chglog_close->setGeometry(405,10,75,25);
    bt_chglog_close->setText("Close");
    bt_chglog_close->hide();

    // Process
    process_file = QString("tmp_file.txt");
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setStandardOutputFile(process_file);
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(executeFinished()));
    connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(executeError(QProcess::ProcessError)));

    process_timer.setInterval(100);
    process_timer.setSingleShot(false);
    connect(&process_timer, SIGNAL(timeout()), this, SLOT(appendOutput()));
}

updatebox::~updatebox()
{
    delete ui;
}

void updatebox::execute(QString command, bool &cursorUp)
{
    QFile::remove(process_file);
    process_file_pos = 0;
    process.start(command);
    process_timer.start();
}

void updatebox::appendOutput()
{
  QFile file(process_file);
  QTextStream read(&file);

  if (!file.open(QIODevice::ReadOnly)) return;
  if (file.size()>process_file_pos)
  {
    file.seek(process_file_pos);
    ui->consoleOutput->moveCursor(QTextCursor::End);
    ui->consoleOutput->insertPlainText(file.readAll());
    process_file_pos = file.pos();
  }
  file.close();
}

void updatebox::executeFinished()
{
  process_timer.stop();
  appendOutput();
  qDebug() << "curs=" << cursorUp;
  if(cursorUp) {
      qDebug() << "Enter loop";
      ui->consoleOutput->moveCursor(QTextCursor::Start);
  }
}

void updatebox::executeError(QProcess::ProcessError)
{
    process_timer.stop();
    appendOutput();
}

void updatebox::changelogMode()
{
    // Layout update
    this->setWindowTitle("AND2 Changelog");
    ui->consoleOutput->clear();
    ui->consoleOutput->setReadOnly(1);
    ui->consoleOutput->setGeometry(20,40,460,340);
    ui->lb_askupdate->hide();
    ui->bt_update->hide();
    ui->lb_changelog->setGeometry(20,10,230,20);
    ui->lb_changelog->setText("Changelog (last 10 revisions) :");
    bt_chglog_close->show();
    connect(bt_chglog_close,SIGNAL(released()),this,SLOT(close()));
}
