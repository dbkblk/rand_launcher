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
bool setGameOption(QString param, QString newValue)
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

QString readGameOption(QString param)
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

QStringList getColorSet()
{
    // Open theme file
    QFile file("Assets/Modules/Interface/Resource/Themes/Civ4/Civ4Theme_Common.thm");
    QStringList result;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream ts(&file);
        while(!ts.atEnd())
        {
            QString line = ts.readLine();
            if(line.contains("GColor\t.BG"))
            {
                QStringList list = line.replace("(","~").replace(")","~").replace(",","~").split("~");
                result << list[1].trimmed();
                result << list[2].trimmed();
                result << list[3].trimmed();
                result << list[4].trimmed();
                //qDebug() << "Color found" << result;
            }
        }
        file.close();
    }

    //qDebug() << "getColorSet()" << result;

    return result;
}

QStringList getColorSetFromName(QString color_name){
    // Open color definition file
    QFile definition("Assets/Modules/Interface/colorSets.xml");
    QDomDocument xml;
    QStringList result;
    if(definition.open(QIODevice::ReadOnly | QIODevice::Text)){
        xml.setContent(&definition);
        definition.close();
        QDomElement color = xml.firstChildElement("root").firstChildElement("color").toElement();
        for(;!color.isNull();color = color.nextSiblingElement()){
            if(color.firstChild().nodeValue() == color_name){
                result << color.attribute("r") << color.attribute("g") << color.attribute("b") << color.attribute("a");
            }
        }
    }
    if(result.isEmpty()){
        // If name is unknown, set default
        result << "69" << "93" << "156" << "217";
        setCheckerParam("Modules/ColorUI", "Default");
    }

    //qDebug() << "getColorSetFromName()" << color_name << result;
    return result;
}

QString getColorName(QStringList color_set){
    // Open color definition file
    QFile definition("Assets/Modules/Interface/colorSets.xml");
    QDomDocument xml;
    QString result = "Custom";
    if(definition.open(QIODevice::ReadOnly | QIODevice::Text)){
        xml.setContent(&definition);
        definition.close();
        QDomElement color = xml.firstChildElement("root").firstChildElement("color").toElement();
        for(;!color.isNull();color = color.nextSiblingElement()){
            QStringList temp;
            temp << color.attribute("r") << color.attribute("g") << color.attribute("b") << color.attribute("a");
            if(temp.join(",") == color_set.join(",")){
                result = color.firstChild().nodeValue();
            }
        }
    }

    //qDebug() << "getColorName()" << color_set << result;

return result;
}

QStringList getColorSetFromNumber(int number){
    // Open color definition file
    QFile definition("Assets/Modules/Interface/colorSets.xml");
    QDomDocument xml;
    int i = 0;
    if(definition.open(QIODevice::ReadOnly | QIODevice::Text)){
        xml.setContent(&definition);
        definition.close();
        QDomElement color = xml.firstChildElement("root").firstChildElement("color").toElement();
        for(;!color.isNull();color = color.nextSiblingElement()){
            if(i == number){
                QStringList temp;
                temp << color.attribute("r") << color.attribute("g") << color.attribute("b") << color.attribute("a");
                //qDebug() << "getColorSetFromNumber()" << i << temp;
                return temp;
            }
            i++;
        }
    }
    //qDebug() << "getColorSetFromNumber()" << "Empty";
    QStringList empty;
    return empty;
}

int getColorNumberFromSet(QStringList color_set){
    // Open color definition file
    QFile definition("Assets/Modules/Interface/colorSets.xml");
    QDomDocument xml;
    int i = 0;
    if(definition.open(QIODevice::ReadOnly | QIODevice::Text)){
        xml.setContent(&definition);
        definition.close();
        QDomElement color = xml.firstChildElement("root").firstChildElement("color").toElement();
        for(;!color.isNull();color = color.nextSiblingElement()){
            QStringList temp;
            temp << color.attribute("r") << color.attribute("g") << color.attribute("b") << color.attribute("a");
            if (temp == color_set){
                //qDebug() << "getColorNumberFromSet()" << color_set << i;
                return i;
            }
            i++;
        }
    }

    //qDebug() << "getColorNumberFromSet()" << "0";

    return 0;
}


void setColorSet(QStringList color_set)
{
    qDebug() << "Interface color set to" << color_set;
    // Open theme file
    QFile file("Assets/Modules/Interface/Resource/Themes/Civ4/Civ4Theme_Common.thm");
    QFile file_out("Assets/Modules/Interface/Resource/Themes/Civ4/Civ4Theme_Common.thm_temp");
    file_out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream ts_out(&file_out);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream ts(&file);
        while(!ts.atEnd())
        {
            QString line = ts.readLine();
            if(line.contains("GColor\t.BG"))
            {
                line = "\t\t\t\tGColor\t.BG\t\t\t\t\t\t\t=\tGColor( " + color_set[0] + ", " + color_set[1] + ", " + color_set[2] + ", " + color_set[3] + ")\t\t:\tGFC_Control_Color;\t//Set for dynamic color change";
            }
            ts_out << line << "\n";
        }
        file.close();
    }


    // Save content back to the file
    file_out.close();
    file.remove();
    file_out.rename("Assets/Modules/Interface/Resource/Themes/Civ4/Civ4Theme_Common.thm");
}

bool setColorCustomDefinition(QStringList color_set){
    // Open color definition file
    QFile definition("Assets/Modules/Interface/colorSets.xml");
    QDomDocument xml;

    if(definition.open(QIODevice::ReadOnly | QIODevice::Text)){
        xml.setContent(&definition);
        definition.close();
        QDomElement color = xml.firstChildElement("root").firstChildElement("color").toElement();
        for(;!color.isNull();color = color.nextSiblingElement()){
                if (color.firstChild().nodeValue() == "Custom"){
                    color.setAttribute("r", color_set[0]);
                    color.setAttribute("g", color_set[1]);
                    color.setAttribute("b", color_set[2]);
                    color.setAttribute("a", color_set[3]);
            }
        }
    }

    // Save file
    definition.remove();
    if(definition.open(QIODevice::Truncate | QIODevice::WriteOnly)){
        QTextStream ts(&definition);
        xml.save(ts, 4);
        definition.close();
        return true;
    }

    return false;
}

void launchGame(QString executable){

    // Check for different mod name
    QString mod_name = "Rise of Mankind - A New Dawn";
    if(readCheckerParam("Mod/mod_name") != "error"){
        mod_name = readCheckerParam("Mod/mod_name");
    }

    // Launch executable
    QStringList arg;
    arg << "mod=\\" + mod_name;
    QProcess update;
    update.startDetached(executable, arg);
}

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

bool readOptionModernFlags()
{
    // Open the file
    QDomDocument read;
    QFile file("Assets/Modules/Modern_flags/MLF_CIV4ModularLoadingControls.xml");
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

bool setOptionModernFlags(bool value)
{
    // Open the file
    QDomDocument read;
    QFile file("Assets/Modules/Modern_flags/MLF_CIV4ModularLoadingControls.xml");

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
    // Rewrite of the setGameOptions
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
    int counter = 0;

    // Reset the first occurence and remove the following
    while(!in_enc.atEnd())
    {
        QString line = in_enc.readLine();
        if(line.contains("GameOptions") && counter == 0)
        {
            line = "GameOptions = ";
            counter++;
            out_enc << line << "\n";
        }
        else if((line.contains("GameOptions") || line.contains("; Game Options")) && counter > 0)
        {
            line = "GameOptions = ";
        }
        else
        {
            out_enc << line << "\n";
        }
    }
    file_in.close();
    file_out.close();
    QFile::remove(ini_orig);
    QFile::rename(ini_temp,ini_orig);
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

void setTextureTerrainSet(int index){
    QStringList known_sets;
    // Texture sets order
    known_sets << "and" << "bluemarble" << "original" << "alternative" << "vincentz";

    // Get the texture to set
    QString texture = known_sets[index];
    QString texture_file_name = "Assets/terrain_textures_" + texture + ".fpk";
    QString texture_archive_name = "Assets/terrain_textures_" + texture + ".tar.xz";

    // Remove that texture from the list
    known_sets.removeAll(texture);

    if(!QFile::exists(texture_file_name)){
        unTarXz(texture_archive_name);
    }
    setCheckerParam("Modules/Terrain",QString::number(index));

    // Remove all other textures
    foreach(QString entry, known_sets){
        QString texture_to_remove = "Assets/terrain_textures_" + entry + ".fpk";
        if(QFile::exists(texture_to_remove)){
            QFile::remove(texture_to_remove);
        }
    }

    // Check if clearing cache is needed (index is different than saved setting)
    if(QString(readCheckerParam("Modules/Terrain")).toInt() != index){
        clearCache();
    }
    qDebug() << "Terrain texture set to" << texture;
}

QString checkMd5(QString file_path){
    // Generate hash of original file
    QFile file(file_path);
    QCryptographicHash crypto(QCryptographicHash::Md5);
    file.open(QFile::ReadOnly);
    while(!file.atEnd()){
        crypto.addData(file.read(8192));
    }
    QByteArray hash = crypto.result().toHex();
    QString hash_string = hash;
    file.close();
    return hash_string;
}
