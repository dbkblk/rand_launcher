#include "w_install.h"
#include "ui_w_install.h"

// TO REVIEW Installation process
/*
w_install::w_install(QDialog *parent) :
  QDialog(parent),
  ui(new Ui::w_install)
{
    // Installation window objects

    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
}

void w_install::on_buttonBox_accepted()
{
    // Setup the initial window and launch checkout command in a box
    QFile::copy("checker/upd_proc.exe","upd_proc.exe");
    QProcess updater;
    updater.startDetached(QString("upd_proc.exe install"));
    QApplication::quit();
}

void w_install::on_buttonBox_rejected()
{
    qApp->exit();
}

void restartLauncher()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}*/
