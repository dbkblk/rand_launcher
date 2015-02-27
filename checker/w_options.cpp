#include "w_options.h"
#include "w_main.h"
#include "w_exclusion.h"
#include "ui_w_options.h"
#include "f_civ.h"

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QtXml>

w_options::w_options(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::w_options)
{
    int init;
    init = 0;

    ui->setupUi(this);

    // Set custom color button
    ui->bt_customColor->setIcon(QIcon("checker/icons/cust.png"));

    // Generate color box
    populateColorBox();

    // Check default states
    int terrain = QString(readCheckerParam("Modules/Terrain")).toInt();
    if(terrain < 5){ui->dd_textures->setCurrentIndex(terrain);}

    if(readOptionFormations() == true)
    {
        // Save parameter
        setCheckerParam("Modules/Formations", "1");
        ui->opt_checkbox_formations->setChecked(1);
    }

    if(readGameOption("Mod") == "Rise of Mankind - A New Dawn") {
        ui->startBox->setChecked(1);
    }

    if(readCheckerParam("Main/QuitLauncher") == "1") {
        ui->checkerBox->setChecked(1);
    }

    // Set default opt_text_path
    qDebug() << "Executable path: " << readCheckerParam("Main/ExecutablePath");
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

void w_options::populateColorBox()
{
    // Open color definition file
    QFile definition("Assets/Modules/Interface/colorSets.xml");
    QDomDocument xml;
    if(definition.open(QIODevice::ReadOnly | QIODevice::Text)){
        xml.setContent(&definition);
        definition.close();
        QDomElement color = xml.firstChildElement("root").firstChildElement("color").toElement();
        for(;!color.isNull();color = color.nextSiblingElement()){
            // Add color to the color box
            QString result = color.firstChild().nodeValue();

            // Rename to known translations
            if(result == "Default"){ui->colorBox->addItem(tr("Dark blue (Default)"));}
            else if(result == "Black"){ui->colorBox->addItem(tr("Black"));}
            else if(result == "Cerulean"){ui->colorBox->addItem(tr("Cerulean"));}
            else if(result == "Coal"){ui->colorBox->addItem(tr("Coal"));}
            else if(result == "Dark Red"){ui->colorBox->addItem(tr("Dark red"));}
            else if(result == "Forest"){ui->colorBox->addItem(tr("Forest"));}
            else if(result == "Purple"){ui->colorBox->addItem(tr("Purple"));}
            else if(result == "Red"){ui->colorBox->addItem(tr("Red"));}
            else if(result == "Silver"){ui->colorBox->addItem(tr("Silver"));}
            else if(result == "Custom"){ui->colorBox->addItem(tr("Custom"));}
            else {ui->colorBox->addItem(result);}
        }
    }

    // Set the color box index
    ui->colorBox->setCurrentIndex(getColorNumberFromSet(getColorSetFromName(readCheckerParam("Modules/ColorUI"))));
}

void w_options::on_colorBox_currentIndexChanged(int index)
{
    //qDebug() << "Index value:" << init;
    if(init == 1){
        QStringList color_set = getColorSetFromNumber(index);
        QString color_name = getColorName(color_set);
        setColorSet(color_set);
        setCheckerParam("Modules/ColorUI",color_name);
    }
    init = 1;
}

void w_options::on_bt_customColor_clicked()
{
    // Get color values
    QStringList color_set = getColorSetFromName("Custom");
    QColor custom = QColorDialog::getColor(QColor(color_set[0].toInt(),color_set[1].toInt(),color_set[2].toInt(),color_set[3].toInt()), this, "Pick a custom color",QColorDialog::ShowAlphaChannel);

    // Save custom color
    if(custom.isValid()){
        color_set.clear();
        color_set << QString::number(custom.red()) << QString::number(custom.green()) << QString::number(custom.blue()) << QString::number(custom.alpha());
        setColorCustomDefinition(color_set);
        setColorSet(color_set);
        setCheckerParam("Modules/ColorUICustom",color_set.join(","));
        ui->colorBox->setCurrentIndex(getColorNumberFromSet(color_set));
    }
    else {
        qDebug() << "Custom color selection aborted.";
    }
}

void w_options::on_startBox_toggled(bool checked)
{
    if(!checked) {
        setGameOption("Mod", "0");
    }
    if(checked) {
        setGameOption("Mod", "Rise of Mankind - A New Dawn");
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
    QString exeloc = QFileDialog::getOpenFileName(0, tr("Find Civ IV executable"), QString(), "(Civ4BeyondSword.exe)");
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
    setTextureTerrainSet(index);
    ui->dd_textures->setCurrentIndex(index);
}


