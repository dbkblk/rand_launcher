#include <w_main.h>
#include <w_options.h>
#include <f_civ.h>
#include <w_install.h>

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
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
        QFile::remove("cygcrypto-1.0.0.dll");
        QFile::remove("cyggcc_s-1.dll");
        QFile::remove("cygiconv-2.dll");
        QFile::remove("cygssp-0.dll");
        QFile::remove("cygwin1.dll");
        QFile::remove("cygz.dll");
        QFile::remove("rsync.exe");
        QFile::remove("upd_proc.exe");
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
    // Create modules
    w_main w;

    // Check for existing installation
    QFile temp("updating");
    if(temp.exists()){
        f_check updater;
        updater.PrepareUpdate();
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("There seems to be a problem with the previous update. Checking file again."));
        msgBox.exec();
        QFile::remove("updating");
        #ifdef _WIN32
        system("taskkill /F rsync.exe");
        #endif
        #ifdef __linux
        system("killall rsync");
        #endif
        updater.ActionUpdate();
        return a.exec();
    }

    QDir assets("Assets");
    if(!assets.exists()){
        qDebug() << "No assets dir, assuming the mod is not installed";

        // Launch updater
        f_check updater;
        updater.PrepareUpdate();
        updater.ActionUpdate();
        return a.exec();
    }

    else{
    // Start the GUI
    w.show();
    }

    return a.exec();
}


