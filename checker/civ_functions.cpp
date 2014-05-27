#include <civ_functions.h>
#include <mainwindow.h>
#include <lib\tinyxml2.h>
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>


using namespace std;



// Set the mod to start by default
bool setConfigParam(QString param, QString newValue)
{
    // Get config paths
    QDir config_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/My Games/Beyond the sword/";
    QString ini_orig = config_path.filePath("CivilizationIV.ini");
    QString ini_temp = config_path.filePath("CivlizationIV.ini.temp");
    QString ini_backup = config_path.filePath("CivilizationIV.bak");

    // Make a backup
    QFile::remove(ini_backup);
    QFile::copy(ini_orig, ini_backup);

    // Set value
    QFile file_in(ini_orig);
    QFile file_out(ini_temp);
    file_in.open(QIODevice::ReadOnly | QIODevice::Text);
    file_out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream in_enc(&file_in);
    QTextStream out_enc(&file_out);
    while(!in_enc.atEnd())
    {
        QString line = in_enc.readLine();
        if(line.contains(param + " ="))
        {
            line = param + " = " + newValue;
        }
        out_enc << line << "\n";
    }
    file_in.close();
    file_out.close();
    QFile::remove(ini_orig);
    QFile::rename(ini_temp,ini_orig);

    qDebug() << "Parameter set to " << newValue;
    return 0;
}

QString readConfigParam(QString param)
{
    // Get config paths
    QDir config_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/My Games/Beyond the sword/";
    QString ini_orig = config_path.filePath("CivilizationIV.ini");

    // Read value
    QFile file_in(ini_orig);
    QString value;
    file_in.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_enc(&file_in);
    while(!in_enc.atEnd())
    {
        QString line = in_enc.readLine();
        if(line.contains(param + " ="))
        {
            line.replace(param + " = ","");
            value = line;
        }
    }
    file_in.close();

    qDebug() << value;
    return value;
}

QString readCheckerParam(QString param)
{
    QSettings settings("checker/checker_config.ini", QSettings::IniFormat);
    qDebug() << settings.status();
    if(!settings.contains(param)) {
        return "error";
    }
    QString value = settings.value(param).toString();
    qDebug() << "Checker parameter set to " << settings.value(param);
    return value;
}

bool setCheckerParam(QString param, QString newValue)
{
    if(!QFile::exists("checker/checker_config.ini")) {
        QFile ch_conf;
        ch_conf.open(QIODevice::WriteOnly);
    }
    QSettings settings("checker/checker_config.ini", QSettings::IniFormat);
    qDebug() << settings.status();
    settings.setValue(param, newValue);
    qDebug() << "Checker parameter set to" <<       settings.value(param);
    return 0;
}




/*const char* readXML(const char* file, const char* tag)
{
    tinyxml2::XMLDocument read;
    read.LoadFile(file);
    const char* value = read.FirstChildElement("versions")->FirstChildElement(tag)->GetText();
    qDebug() << "readXML : " << value;
    return value;
}

bool writeXML(const char* file, const char* tag, const char* newValue)
{
    tinyxml2::XMLDocument read;
    read.LoadFile(file);
    read.FirstChildElement("versions")->FirstChildElement(tag)->SetText(newValue);
    read.SaveFile(file);
    return 0;
}*/

const char* readColors()
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    if (!read.ErrorID() == 0){
        qDebug() << "The file couldn't be read : " << read.ErrorID();
        return 0;
    }

    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    // Loop
    for(;; value_el=value_el->NextSiblingElement() ) {
        const char* value = value_el->FirstChildElement("Directory")->GetText();
        const char* bLoad = value_el->FirstChildElement("bLoad")->GetText();

        if (!strcmp(bLoad, "1")) {
            return value;
        }

    }
    return 0;
}

int readColorsCounter()
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    if (!read.ErrorID() == 0){
        qDebug() << "The file couldn't be read : " << read.ErrorID();
        return 99;
    }
    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();
    // Loop
    int counter = -1;
    for(;; value_el=value_el->NextSiblingElement() ) {

        const char* bLoad = value_el->FirstChildElement("bLoad")->GetText();
        counter++;
        if (!strcmp(bLoad, "1")) {
            return counter;
        }
        if (counter == 7)
        {
            return 0;
        }
    }
    return 99;
}

bool setColors(const char* color)
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    const char* resetValue = "0";
    if (!read.ErrorID() == 0){
        qDebug() << "The file couldn't be read : " << read.ErrorID();
        return 1;
    }


    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    // Reset all values
    for(value_el; value_el; value_el=value_el->NextSiblingElement() ) {
        value_el->FirstChildElement("bLoad")->SetText(resetValue);
    }

    tinyxml2::XMLElement* valueSet_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    for(valueSet_el; valueSet_el; valueSet_el=valueSet_el->NextSiblingElement() ) {
        const char* txtValue = valueSet_el->FirstChildElement("Directory")->GetText();
        if (strcmp(txtValue ,color) == 0) {
            valueSet_el->FirstChildElement("bLoad")->SetText("1");
        }
    }
    read.SaveFile(file);
    return 0;
}

void launchGame(){
    QString bt_exe = readCheckerParam("Main/ExecutablePath");
    QUrl u = QUrl::fromLocalFile(bt_exe);
    QDesktopServices::openUrl(QUrl(u));
}

QString check_addon_mcp()
{
    QFile addon_MCP_file("Assets/Addon_MCP.ini");
    QFile addon_MCP_file2("Assets/MCP0.FPK");
    if(addon_MCP_file2.exists() == true)
    {
        if(addon_MCP_file.exists() == true)
        {
            qDebug() << "Civ Mega Pack detected";
            QSettings addon_MCP_settings("Assets/Addon_MCP.ini", QSettings::IniFormat);
            QString MCP_version = addon_MCP_settings.value("Main/Version").toString();

            setCheckerParam("ADDON_MEGACIVPACK/FilesVersion",MCP_version);
            return MCP_version;
        }
        else
        {
            setCheckerParam("ADDON_MEGACIVPACK/FilesVersion","Unknown");
            return "Unknown";
        }

    }
    else
    {
        qDebug() << "Civ Mega Pack not detected";
        setCheckerParam("ADDON_MEGACIVPACK/FilesVersion","Not installed");
        return "Not installed";
    }
}

QString check_addon_more_music()
{
    QFile addon_audio_file("Assets/Addon_audio.ini");
    QDir addon_audio_new("Assets/Sounds/Addon_audio");
    QDir addon_audio_old("Assets/Sounds/NEW");

    if (addon_audio_new.exists() == true || addon_audio_old.exists() == true)
    {
        qDebug() << "More music detected";
        if(addon_audio_file.exists() == true)
        {
            QSettings addon_audio_settings("Assets/Addon_audio.ini", QSettings::IniFormat);
            QString audio_version = addon_audio_settings.value("Main/Version").toString();

            setCheckerParam("ADDON_MOREMUSIC/Version",audio_version);
            return audio_version;
        }
        else
        {
            setCheckerParam("ADDON_MOREMUSIC/Version","Unknown");
            return "Unknown";
        }

    }
    else
    {
        qDebug() << "More music not detected";
        setCheckerParam("ADDON_MOREMUSIC/Version","Not installed");
        return "Not installed";
    }
}

QString check_addon_more_handicaps()
{
    QFile addon_handicaps_file("Assets/Addon_handicap.ini");
    if(addon_handicaps_file.exists() == true)
    {
        qDebug() << "More handicaps detected";
        QSettings addon_handicaps_settings("Assets/Addon_handicap.ini", QSettings::IniFormat);
        QString handicaps_version = addon_handicaps_settings.value("Main/Version").toString();

        setCheckerParam("ADDON_MOREHANDICAPS/Version",handicaps_version);

        return handicaps_version;
    }
    else
    {
        qDebug() << "More handicaps not detected";
        setCheckerParam("ADDON_MOREHANDICAPS/Version","Not installed");
        return "Not installed";
    }
}

bool readOptionFormations()
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Formations/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    if (!read.ErrorID() == 0){
        qDebug() << "The file couldn't be read : " << read.ErrorID();
        return 0;
    }

    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    const char* bLoad = value_el->FirstChildElement("bLoad")->GetText();
    QString temp;
    temp = bLoad;

    if (temp.toInt() == 1) {
        return true;
    }
    return false;
}

bool setOptionFormations(bool value)
{
    // Open the file
    tinyxml2::XMLDocument read;
    const char* file = "Assets/Modules/Formations/MLF_CIV4ModularLoadingControls.xml";
    read.LoadFile(file);
    if (!read.ErrorID() == 0){
        qDebug() << "The file couldn't be read : " << read.ErrorID();
        return 1;
    }

    // Go to color level
    tinyxml2::XMLElement* value_el = read.FirstChildElement("Civ4ModularLoadControls")->FirstChildElement("ConfigurationInfos")->FirstChildElement("ConfigurationInfo")->FirstChildElement("Modules")->FirstChildElement("Module")->ToElement();

    // Set values
    if (value)
    {
        value_el->FirstChildElement("bLoad")->SetText("1");
    }
    else
    {
        value_el->FirstChildElement("bLoad")->SetText("0");
    }
    read.SaveFile(file);
    return 0;
}
