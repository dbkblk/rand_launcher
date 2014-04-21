#include "optionbox.h"
#include "ui_optionbox.h"
#include "civ_functions.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QSettings>

optionBox::optionBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optionBox)
{
    ui->setupUi(this);

    // Set the detected color
    ui->colorBox->setCurrentIndex(readColorsCounter());

    // Set default startBox state
    if(readConfigParam("CONFIG/Mod") == "Mods/Rise of Mankind - A New Dawn") {
        ui->startBox->setChecked(1);
    }
    else
        ui->startBox->setChecked(0);
}

optionBox::~optionBox()
{
    delete ui;
}

// Buttons actions

void optionBox::on_opt_bt_update_clicked()
{
    checkUpdate();
    QMessageBox::information(this, "Information", "The mod is up-to-date.");
}

void optionBox::on_opt_bt_cleanup_clicked()
{
    cleanUp();
    QMessageBox::information(this, "Information", "The mod has been cleaned up. You can update the game now (it can grab the missing files).");
}

void optionBox::on_opt_bt_restore_clicked()
{
    rollBack();
    QMessageBox::information(this, "Information", "The mod has been reverted to the previous version.");
}

void optionBox::on_opt_bt_chooserev_clicked()
{
    QString dial_rev = QInputDialog::getText(this, "Revision selector", "Please enter the revision you want to revert to :", QLineEdit::Normal);
    qDebug() << dial_rev;

    char cmd[100];
    sprintf(cmd, "checker\\svn.exe update -r %s --accept theirs-full && echo The cache will now be cleared && TIMEOUT 3", dial_rev.toStdString().c_str());
    qDebug() << cmd;
    system(cmd);
    QString message = "The mod has been reverted to the revision " + dial_rev;
    QMessageBox::information(this, "Information", message);
}

void optionBox::on_colorBox_currentIndexChanged(const QString &colorName)
{
    QString colorUI = colorName + " UI";
    setColors(colorUI.toStdString().c_str());
}

void optionBox::on_startBox_toggled(bool checked)
{
    if(!checked) {
        setConfigParam("CONFIG/Mod", "0");
    }
    if(checked) {
        setConfigParam("CONFIG/Mod", "Mods/Rise of Mankind - A New Dawn");
    }
}
