#include "mainwindow.h"
#include "optionbox.h"
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QDir>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Check architecture
    BOOL b_64BitOpSys;
    #ifdef _WIN64
        b_64BitOpSys = TRUE
    #else
        IsWow64Process(GetCurrentProcess(), &b_64BitOpSys);
    #endif

    // Check directory from registry
    QSettings CivRegistry;
    if(readCheckerParam("MAIN/ExecutablePath") == "error")
    {
        if (b_64BitOpSys == 1)
        {
            qDebug() << "64bits detected";
            QSettings CivRegistry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Firaxis Games\\Sid Meier's Civilization 4 - Beyond the Sword", QSettings::NativeFormat);
            QString Civ4Path = CivRegistry.value("installdir").toString().replace("\\","/") + "/Civ4BeyondSword.exe";
            qDebug() << "Auto-detected Civ Path : " << Civ4Path;
            setCheckerParam("MAIN/ExecutablePath",Civ4Path);
        }
        else
        {
            qDebug() << "32bits detected";
            QSettings CivRegistry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Firaxis Games\\Sid Meier's Civilization 4 - Beyond the Sword", QSettings::NativeFormat);
            QString Civ4Path = CivRegistry.value("installdir").toString().replace("\\","/") + "\\Civ4BeyondSword.exe";
            qDebug() << "Auto-detected Civ Path : " << Civ4Path;
            setCheckerParam("MAIN/ExecutablePath",Civ4Path);
        }

    }

    // Check for correct path

    QDir BTS_dir("../../../Beyond the sword");
    if(!BTS_dir.exists()){
        qDebug() << "Launcher is in a wrong path";
        QMessageBox::critical(0, "Error", "The launcher isn't in the right directory. It should be either in 'My Documents/My Games/Beyond the sword/Mods/Rise of Mankind - A New Dawn' or in 'Civilization IV (root game folder)/Beyond the sword/Mods/Rise of Mankind - A New Dawn'");
        return 1;
    }

    // Start the GUI
    QApplication a(argc, argv);
    MainWindow w;
    installBox install;

/*    // Cleanup update output

    QFile update_output("update_out.ini");
    if(update_output.exists()) {
        QProcess::startDetached("taskkill /f /im upd_proc.exe");
        update_output.remove();
        QDir temp("temp");
        temp.rmdir("temp");
    }
*/

    // Check for installation

    QDir svn_dir(".svn");
    if(!svn_dir.exists()){
        qDebug() << "Directory .svn not found";
        install.show();

    }
    else {
        qDebug() << "SVN directory detected";
        w.show();
    }

    return a.exec();
}


