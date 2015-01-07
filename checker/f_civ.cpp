#include <f_civ.h>
#include <w_main.h>

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>
#include <QtXml/QtXml>

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

    //qDebug() << "Parameter set to " << newValue;
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

    return value;
}

QString readCheckerParam(QString param)
{
    QSettings settings("checker/checker_config.ini", QSettings::IniFormat);
    if(!settings.contains(param)) {
        return "error";
    }
    QString value = settings.value(param).toString();
    return value;
}

bool setCheckerParam(QString param, QString newValue)
{
    if(!QFile::exists("checker/checker_config.ini")) {
        QFile ch_conf;
        ch_conf.open(QIODevice::WriteOnly);
    }
    QSettings settings("checker/checker_config.ini", QSettings::IniFormat);
    //qDebug() << settings.status();
    settings.setValue(param, newValue);
    //qDebug() << "Checker parameter set to" <<       settings.value(param);
    return 0;
}

int readColorsCounter()
{
    // Open the file
    QDomDocument read;
    QFile file("Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
         return 0;
     }
    read.setContent(&file);

    // Go to color level
    QDomElement value_el = read.firstChildElement("Civ4ModularLoadControls").firstChildElement("ConfigurationInfos").firstChildElement("ConfigurationInfo").firstChildElement("Modules").firstChildElement("Module").toElement();

    // Loop
    int counter = 0;
    for(;; value_el=value_el.nextSiblingElement() ) {

        QString bLoad = value_el.firstChildElement("bLoad").text();
        counter++;

        if (bLoad == "1") {
            //qDebug() << "Counter is " << counter;
            file.close();
            return counter;
        }
        if (counter == 7)
        {
            file.close();
            return 0;
        }
    }
    file.close();
    return 99;
}

bool setColors(int index)
{
    // Convert the index into a string
    QString colorUI;
    switch (index)
    {
    case 0:
       colorUI = "default";
       break;

    case 1:
       colorUI = "Black UI";
       break;

    case 2:
       colorUI = "Coal UI";
       break;

    case 3:
       colorUI = "Dark Red UI";
       break;

    case 4:
       colorUI = "Forest UI";
       break;

    case 5:
       colorUI = "Purple UI";
       break;

    case 6:
       colorUI = "Red UI";
       break;

    case 7:
       colorUI = "Silver UI";
       break;

    case 8:
       colorUI = "Cerulean UI";
       break;
    }

    // Open the file
    QDomDocument read;
    QFile file("Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening Assets/Modules/Interface Colors/MLF_CIV4ModularLoadingControls.xml";
         return 0;
     }
    read.setContent(&file);
    file.close();

    // Go to color level
    QDomElement color_element = read.firstChildElement("Civ4ModularLoadControls").firstChildElement("ConfigurationInfos").firstChildElement("ConfigurationInfo").firstChildElement("Modules").firstChildElement("Module").toElement();

    // Reset all values
    for(color_element ; !color_element.isNull(); color_element=color_element.nextSiblingElement() ) {
        color_element.firstChildElement("bLoad").firstChild().setNodeValue("0");
        }

        if(colorUI != "default"){
        color_element = read.firstChildElement("Civ4ModularLoadControls").firstChildElement("ConfigurationInfos").firstChildElement("ConfigurationInfo").firstChildElement("Modules").firstChildElement("Module").toElement();

        for(color_element ; !color_element.isNull(); color_element=color_element.nextSiblingElement() ) {
            QString txtValue = color_element.firstChildElement("Directory").firstChild().nodeValue();
            if (txtValue == colorUI) {
                color_element.firstChildElement("bLoad").firstChild().setNodeValue("1");
            }
        }
    }

    // Save content back to the file
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        return 0;
    }
    file.write(read.toByteArray());
    file.close();
    return 0;
}

void launchGame(){
    QString bt_exe = readCheckerParam("Main/ExecutablePath");
    QStringList arg;
    arg << "mod=\\Rise of Mankind - A New Dawn";
    QProcess update;
    update.startDetached(bt_exe, arg);
    //QUrl u = QUrl::fromLocalFile(bt_exe);
    //QDesktopServices::openUrl(QUrl(u));
}

/*QString check_addon_mcp()
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
}*/

bool readOptionFormations()
{
    // Open the file
    QDomDocument read;
    QFile file("Assets/Modules/Formations/MLF_CIV4ModularLoadingControls.xml");
    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening file";
         return 0;
     }
    read.setContent(&file);
    file.close();

    // Go to color level
    QDomElement value_el = read.firstChildElement("Civ4ModularLoadControls").firstChildElement("ConfigurationInfos").firstChildElement("ConfigurationInfo").firstChildElement("Modules").firstChildElement("Module").toElement();

    QString bLoad = value_el.firstChildElement("bLoad").firstChild().nodeValue();

    if (bLoad.toInt() == 1) {
        return true;
    }
    return false;
}

bool setOptionFormations(bool value)
{
    // Open the file
    QDomDocument read;
    QFile file("Assets/Modules/Formations/MLF_CIV4ModularLoadingControls.xml");

    if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error opening file";
         return 0;
     }
    read.setContent(&file);
    file.close();

    // Go to color level
    QDomElement value_el = read.firstChildElement("Civ4ModularLoadControls").firstChildElement("ConfigurationInfos").firstChildElement("ConfigurationInfo").firstChildElement("Modules").firstChildElement("Module").toElement();

    // Set values
    if (value)
    {
        value_el.firstChildElement("bLoad").firstChild().setNodeValue("1");
    }
    else
    {
        value_el.firstChildElement("bLoad").firstChild().setNodeValue("0");
    }

    // Save content back to the file
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);
    file.write(read.toByteArray());
    file.close();

    return 0;
}

bool clearCache()
{
    // Getting the cache path
    QString cacheDir;
    QString finalDir = "\\My Games\\Beyond the Sword\\cache\\";
    char* Appdata = getenv("LOCALAPPDATA");
    cacheDir = Appdata + finalDir;
    qDebug() << "Cache found at " << cacheDir;
    QDir cache(cacheDir);
    cache.removeRecursively();

    return 0;
}

bool clearGameOptions()
{
    setConfigParam("GameOptions","");
    qDebug() << "Cleared parameters";
    return 0;
}

int checkDoubleInstallation()
{
    int counter = 0;
    // Check My Docs standard path
    QDir mydocs_dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/My Games/Beyond the sword/Mods/Rise of Mankind - A New Dawn/";
    if(mydocs_dir.exists()){counter++;qDebug() << "My docs path detected";};

    // Check base game standard path
    QString base_path = readCheckerParam("Main/ExecutablePath");
    base_path.remove("Civ4BeyondSword.exe");
    base_path.append("Mods/Rise of Mankind - A New Dawn");
    QDir base_dir(base_path);
    if(base_dir.exists()){counter++;qDebug() << "Standard path detected";};
    return counter;
}

void unTarXz(QString file){
    QStringList split = file.split("/");
    split.removeLast();
    QFile::copy(QString(file),"temp.tar.xz");
    QProcess unzip;
    unzip.execute(tools::TOOL_XZ + "temp.tar.xz");
    unzip.execute(tools::TOOL_TAR + "temp.tar");
    QFile::remove("temp.tar");
}

