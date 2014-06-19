#include "optionbox.h"
#include "mainwindow.h"
#include "ui_optionbox.h"
#include "civ_functions.h"
#include "updatemanager.h"
#include "updatebox.h"
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>

optionBox::optionBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::optionBox)
{
    ui->setupUi(this);

    // Set the detected color
    int color = readColorsCounter();
    qDebug() << "Counter is " << color;
    ui->colorBox->setCurrentIndex(color);

    // Check default states

    if(readOptionFormations() == true)
    {
        ui->opt_checkbox_formations->setChecked(1);
    }
    else
    {
        ui->opt_checkbox_formations->setChecked(0);
    }

    if(readConfigParam("Mod") == "Rise of Mankind - A New Dawn") {
        ui->startBox->setChecked(1);
    }
    else {
        ui->startBox->setChecked(0);
    }

    if(readCheckerParam("Main/QuitLauncher") == "1") {
        ui->checkerBox->setChecked(1);
    }

    else {
        ui->checkerBox->setChecked(0);
    }

    if(readCheckerParam("Main/CheckerAutoUpdate") == "1")
    {
        ui->opt_checkbox_autoupdate->setChecked(1);
    }
    else
    {
        ui->opt_checkbox_autoupdate->setChecked(0);
    }

    // Set default opt_text_path
    qDebug() << "Check reading : " << readCheckerParam("Main/ExecutablePath");
    if(readCheckerParam("Main/ExecutablePath") == "error")
    {
        ui->opt_text_path->setText(tr("No path specified"));
    }
    else {
        ui->opt_text_path->setText(readCheckerParam("Main/ExecutablePath"));
    }

}

optionBox::~optionBox()
{
    delete ui;
}

void optionBox::reTranslate()
{
    ui->retranslateUi(this);
}

void optionBox::on_colorBox_currentIndexChanged()
{
    int index = ui->colorBox->currentIndex();
    QString colorUI;
    switch (index)
    {
    case 0:
       colorUI = "Black UI";
       break;

    case 1:
       colorUI = "Coal UI";
       break;

    case 2:
       colorUI = "Dark Red UI";
       break;

    case 3:
       colorUI = "Forest UI";
       break;

    case 4:
       colorUI = "Purple UI";
       break;

    case 5:
       colorUI = "Red UI";
       break;

    case 6:
       colorUI = "Silver UI";
       break;

    case 7:
       colorUI = "Cerulean UI";
       break;
    }
    setColors(colorUI);
}

void optionBox::on_startBox_toggled(bool checked)
{
    if(!checked) {
        setConfigParam("Mod", "0");
    }
    if(checked) {
        setConfigParam("Mod", "Rise of Mankind - A New Dawn");
    }
}

void optionBox::on_checkerBox_toggled(bool checked)
{
    if(checked) {
        setCheckerParam("Main/QuitLauncher", "1");
    }
    if(!checked) {
        setCheckerParam("Main/QuitLauncher", "0");
    }
}

void optionBox::on_opt_bt_path_clicked()
{
    QString exeloc = QFileDialog::getOpenFileName(0, "Find Civ. IV executable", QString(), "(Civ4BeyondSword.exe)");
    setCheckerParam("Main/ExecutablePath",exeloc);
    if(exeloc != NULL) {
        ui->opt_text_path->setText(exeloc);
        QMessageBox::information(0, "Information", tr("The game path has been changed"));
        return;
    }
    if(exeloc == NULL) {
        ui->opt_text_path->setText(tr("No game path specified."));
        return;
    }
}


void optionBox::on_opt_bt_chklauncher_clicked()
{
     if(LauncherVersionCalculation())
     {
         QMessageBox upd_box;
         upd_box.setWindowTitle(tr("Launcher update available"));
         upd_box.setText(tr("An update of the launcher is available."));
         upd_box.setInformativeText(tr("Do you want to update ?"));
         upd_box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
         int ret = upd_box.exec();
         switch (ret) {
             case QMessageBox::Ok :
                 ActionLauncherUpdate();
                 break;

             case QMessageBox::Cancel :
                 break;
         }

     }
     else
     {
         QMessageBox::information(0, "Information", tr("No update is available !"));
     }
}

void optionBox::on_opt_checkbox_formations_toggled(bool checked)
{
    if(checked)
    {
        setOptionFormations(true);
    }
    else
    {
        setOptionFormations(false);
    }
}

void optionBox::on_opt_checkbox_autoupdate_toggled(bool checked)
{
    if(checked)
    {
        setCheckerParam("Main/CheckerAutoUpdate","1");
    }
    else
    {
        setCheckerParam("Main/CheckerAutoUpdate","0");
    }

}

