#include "w_install.h"
#include "f_check.h"

// TO REVIEW Installation process

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

}

void w_install::on_buttonBox_rejected()
{
    qApp->exit();
}

void restartLauncher()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}
