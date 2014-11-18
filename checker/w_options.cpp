#include "w_options.h"
#include "w_main.h"
#include "ui_w_options.h"
#include "f_civ.h"

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>

w_options::w_options(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::w_options)
{
    ui->setupUi(this);

    // Set the detected color
    int color = readColorsCounter();
    ui->colorBox->setCurrentIndex(color);

    // Check default states

    if(readOptionFormations() == true)
    {
        ui->opt_checkbox_formations->setChecked(1);
    }

    if(readConfigParam("Mod") == "Rise of Mankind - A New Dawn") {
        ui->startBox->setChecked(1);
    }

    if(readCheckerParam("Main/QuitLauncher") == "1") {
        ui->checkerBox->setChecked(1);
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

w_options::~w_options()
{
    delete ui;
}

void w_options::on_colorBox_currentIndexChanged(int index)
{
    if(index==-1){return;};
    qDebug() << "Index is " << index;
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

void w_options::on_startBox_toggled(bool checked)
{
    if(!checked) {
        setConfigParam("Mod", "0");
    }
    if(checked) {
        setConfigParam("Mod", "Rise of Mankind - A New Dawn");
    }
}

void w_options::on_checkerBox_toggled(bool checked)
{
    if(checked) {
        setCheckerParam("Main/QuitLauncher", "1");
    }
    if(!checked) {
        setCheckerParam("Main/QuitLauncher", "0");
    }
}

void w_options::on_opt_bt_path_clicked()
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

void w_options::on_opt_checkbox_formations_toggled(bool checked)
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

void w_options::on_opt_checkbox_bluemarble_toggled(bool checked)
{
    if(checked)
    {
        QProcess unzip;
        unzip.execute(tools::TOOL_EXTRACT + "Assets/BlueMarble.zip -oAssets/ -y");
    }
    else
    {
        QFile::remove("Assets/BlueMarble.FPK");
    }

}
