#include "w_options.h"
#include "w_main.h"
#include "w_exclusion.h"
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
    setCheckerParam("Modules/ColorUI",QString::number(color));

    // Check default states
    int terrain = QString(readCheckerParam("Modules/Terrain")).toInt();
    if(terrain < 5){ui->dd_textures->setCurrentIndex(terrain);}

    if(readOptionFormations() == true)
    {
        // Save parameter
        setCheckerParam("Modules/Formations", "1");
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
    setCheckerParam("Modules/ColorUI",QString::number(index));
    setColors(index);
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
        setCheckerParam("Modules/Formations", "1");
        setOptionFormations(true);
    }
    else
    {
        setCheckerParam("Modules/Formations", "0");
        setOptionFormations(false);
    }
}

void w_options::on_bt_exclusions_clicked()
{
    exclusion = new w_exclusion(this);
    exclusion->show();
}

void w_options::on_dd_textures_currentIndexChanged(int index)
{
    // Check if clearing cache is needed (index is different than saved setting)
    if(QString(readCheckerParam("Modules/Terrain")).toInt() != index){
        clearCache();
    }

    // Texture change
    if(index == 0) // AND default textures
    {
        if(!QFile::exists("Assets/terrain_textures_and.fpk")){
            unTarXz("Assets/terrain_textures_and.tar.xz");
            QFile::remove("Assets/terrain_textures_original.fpk");
            QFile::remove("Assets/terrain_textures_bluemarble.fpk");
            QFile::remove("Assets/terrain_textures_alternative.fpk");
            QFile::remove("Assets/terrain_textures_vincentz.fpk");
            setCheckerParam("Modules/Terrain","0");
        }
    }
    if(index == 1) // Blue Marble
    {
        if(!QFile::exists("Assets/terrain_textures_bluemarble.fpk")){
            unTarXz("Assets/terrain_textures_bluemarble.tar.xz");
            QFile::remove("Assets/terrain_textures_original.fpk");
            QFile::remove("Assets/terrain_textures_and.fpk");
            QFile::remove("Assets/terrain_textures_alternative.fpk");
            QFile::remove("Assets/terrain_textures_vincentz.fpk");
            setCheckerParam("Modules/Terrain","1");
        }
    }
    if(index == 2) // Original enhanced
    {
        if(!QFile::exists("Assets/terrain_textures_original.fpk")){
            unTarXz("Assets/terrain_textures_original.tar.xz");
            QFile::remove("Assets/terrain_textures_bluemarble.fpk");
            QFile::remove("Assets/terrain_textures_and.fpk");
            QFile::remove("Assets/terrain_textures_alternative.fpk");
            QFile::remove("Assets/terrain_textures_vincentz.fpk");
            setCheckerParam("Modules/Terrain","2");
        }
    }
    if(index == 3) // Sparth
    {
        if(!QFile::exists("Assets/terrain_textures_alternative.fpk")){
            unTarXz("Assets/terrain_textures_alternative.tar.xz");
            QFile::remove("Assets/terrain_textures_bluemarble.fpk");
            QFile::remove("Assets/terrain_textures_and.fpk");
            QFile::remove("Assets/terrain_textures_original.fpk");
            QFile::remove("Assets/terrain_textures_vincentz.fpk");
            setCheckerParam("Modules/Terrain","3");
        }
    }
    if(index == 4) // Vincentz
    {
        if(!QFile::exists("Assets/terrain_textures_vincentz.fpk")){
            unTarXz("Assets/terrain_textures_vincentz.tar.xz");
            QFile::remove("Assets/terrain_textures_bluemarble.fpk");
            QFile::remove("Assets/terrain_textures_and.fpk");
            QFile::remove("Assets/terrain_textures_original.fpk");
            QFile::remove("Assets/terrain_textures_alternative.fpk");
            setCheckerParam("Modules/Terrain","4");
        }
    }
}
