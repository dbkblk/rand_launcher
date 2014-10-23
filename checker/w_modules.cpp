#include "w_modules.h"
#include "ui_w_modules.h"
#include "f_civ.h"

#include <QtCore>

w_modules::w_modules(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::w_modules)
{
    ui->setupUi(this);

    // Set version label
    ui->bt_update->hide();
}

w_modules::~w_modules()
{
    delete ui;
}

void w_modules::on_bt_update_clicked()
{
    if(core->isSelected())
    {
        QFile::copy("checker/upd_proc.exe","upd_proc.exe");
        QProcess updater;
        updater.startDetached(QString("upd_proc.exe update %1").arg(readCheckerParam("Main/LocalRev").toInt()));
        QApplication::quit();
    }

}
