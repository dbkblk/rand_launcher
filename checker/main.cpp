#include <w_main.h>
#include <w_options.h>
#include <f_civ.h>
#include <f_mods.h>
#include <w_install.h>

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QtXml>
#include <QDir>
//

/* Antoine de Saint-Exupéry :
 * 'Perfection is achieved, not when there is nothing more to add, but when there is nothing left to take away.'
 * (so please tell me if you've found something superficial) */

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* Windows specific code */
    // Check architecture
    #ifdef _WIN32
    #include <windows.h>

    BOOL b_64BitOpSys;
    #ifdef _WIN64
        b_64BitOpSys = TRUE;
    #else
        IsWow64Process(GetCurrentProcess(), &b_64BitOpSys);
    #endif

    // Check directory from registry
    if(readCheckerParam("Main/ExecutablePath") == "error")
    {
        if (b_64BitOpSys == 1)
        {
            qDebug() << "64bits detected";
            QSettings CivRegistry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Firaxis Games\\Sid Meier's Civilization 4 - Beyond the Sword", QSettings::NativeFormat);
            QString Civ4Path = CivRegistry.value("installdir").toString().replace("\\","/") + "/Civ4BeyondSword.exe";
            qDebug() << "Auto-detected Civ Path : " << Civ4Path;
            setCheckerParam("Main/ExecutablePath",Civ4Path);
        }
        else
        {
            qDebug() << "32bits detected";
            QSettings CivRegistry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Firaxis Games\\Sid Meier's Civilization 4 - Beyond the Sword", QSettings::NativeFormat);
            QString Civ4Path = CivRegistry.value("installdir").toString().replace("\\","/") + "\\Civ4BeyondSword.exe";
            qDebug() << "Auto-detected Civ Path : " << Civ4Path;
            setCheckerParam("Main/ExecutablePath",Civ4Path);
        }

    }

    // Go out of update
    if(QFile::exists("upd_proc.exe") || QFile::exists("rsync.exe"))
    {
        clearCache();
        clearGameOptions();
        QFile::remove("cyggcc_s-1.dll");
        QFile::remove("cygiconv-2.dll");
        QFile::remove("cygwin1.dll");
        QFile::remove("rsync.exe");
        QFile::remove("upd_proc.exe");
    }

    // Check for double installation
    if(checkDoubleInstallation()>1){
        QMessageBox::critical(0, "Error", QObject::tr("The mod installation was detected in double. This can cause unexpected problems. Please check for the mod folder in these two locations and delete the wrong one:\n- My Documents/My Games/Beyond the Sword/Mods \n- Game folder installation/Beyond the Sword/Mods"));
    }

    // Check for correct path

    QDir BTS_dir("../../Mods");
    if(!BTS_dir.exists()){
        qDebug() << "Launcher is in a wrong path";
        QMessageBox::critical(0, "Error", QObject::tr("The launcher isn't in the right directory. It should be either in 'My Documents/My Games/Beyond the sword/Mods/Rise of Mankind - A New Dawn' or in 'Civilization IV (root game folder)/Beyond the sword/Mods/Rise of Mankind - A New Dawn'"));
        return 1;
    }
    #endif
    /* End of the windows specific code */

    // Regenerate mod exclusion file
    generateModsExclusion();
    generateModsMLFFile();

    // Inject saved color UI and formations parameters to xml files in case of update
    if(readCheckerParam("Modules/Formations") == "1" && readOptionFormations() == false){
        qDebug() << "Inject formation setting to xml";
        setOptionFormations(true);
    }
    // Check color set is conform to the saved parameter
    if(readCheckerParam("Modules/ColorUI") == "Custom"){
        QString color = readCheckerParam("Modules/ColorUICustom");
        QStringList color_set = color.replace("\"","").split(",");
        if(getColorSetFromName("Custom") != color_set){
            qDebug() << "Inject custom color definition";
            setColorCustomDefinition(color_set);
        }
        if(getColorSet() != color_set){
            qDebug() << "Inject custom color UI to xml";
            setColorSet(color_set);
        }
    }
    else{
        if(getColorSet() != getColorSetFromName(readCheckerParam("Modules/ColorUI"))){
            qDebug() << "Inject color UI to xml";
            setColorSet(getColorSetFromName(readCheckerParam("Modules/ColorUI")));
        }
    }

    // Create exclusions.custom.xml if not exist
    QFile exclusion("checker/exclusions.custom.xml");
    if(!exclusion.exists()){
        qDebug() << "No existing custom exclusion file, writing new one.";
        exclusion.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QDomDocument xml_exclusion;
        QDomNode declaration = xml_exclusion.createProcessingInstruction("xml",QString("version=\"1.0\" encoding=\"UTF-8\""));
        xml_exclusion.insertBefore(declaration,xml_exclusion.firstChild());
        QDomNode root = xml_exclusion.createElement("exclusions");
        xml_exclusion.appendChild(root);
        QDomComment comment = xml_exclusion.createComment("Put your custom files inside \"entity\" tags");
        root.appendChild(comment);
        QDomNode entity = xml_exclusion.createElement("entity");
        root.appendChild(entity);

        // Save file
        exclusion.write(xml_exclusion.toByteArray());
        exclusion.close();
    }

    // Checking terrain art
    QString terrain = readCheckerParam("Modules/Terrain");
    if(terrain == "error"){
        setTextureTerrainSet(0);
    }
    else{
        setTextureTerrainSet(terrain.toInt());
    }

    // Create modules
    w_main w;

    // Check for existing installation
    QFile temp("updating");
    QFile reset("reset");
    if(temp.exists() || reset.exists()){
        f_check updater;
        updater.PrepareUpdate();
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("There seems to be a problem with the previous update. Checking file again."));
        msgBox.exec();
        #ifdef _WIN32
        system("taskkill /IM rsync.exe");
        #endif
        #ifdef __linux
        system("killall rsync");
        #endif
        if(temp.exists()){
            QFile::remove("updating");
            updater.ActionUpdate();
        }
        if(reset.exists()){
            QFile::remove("reset");
            updater.ActionReset();
        }
        qDebug("Closing UI");
        w.close();
        return 0;
    }

    QDir assets("Assets");
    if(!assets.exists()){
        qDebug() << "No assets dir, assuming the mod is not installed";

        // Launch updater
        f_check updater;
        updater.PrepareUpdate();
        updater.ActionUpdate();
        return 0;
    }

    else{
    // Start the GUI
        w.show();
    }

    return a.exec();
}


