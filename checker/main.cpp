#include <w_main.h>
#include <w_options.h>
#include <f_civ.h>
#include <w_install.h>

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QDir>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Check architecture
    BOOL b_64BitOpSys;
    #ifdef _WIN64
        b_64BitOpSys = TRUE
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
    if(QFile::exists("upd_proc.exe"))
    {
        clearCache();
        clearGameOptions();
        QFile::remove("upd_proc.exe");
    }

    // Check for correct path

    QDir BTS_dir("../../Mods");
    if(!BTS_dir.exists()){
        qDebug() << "Launcher is in a wrong path";
        QMessageBox::critical(0, "Error", QObject::tr("The launcher isn't in the right directory. It should be either in 'My Documents/My Games/Beyond the sword/Mods/Rise of Mankind - A New Dawn' or in 'Civilization IV (root game folder)/Beyond the sword/Mods/Rise of Mankind - A New Dawn'"));
        return 1;
    }

    // Start the GUI
    w_main w;
    w_install install;

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
    QDir assets_dir("Assets");
    if(!svn_dir.exists()){
        qDebug() << "Directory .svn not found";
        install.show();

    }
    else if(!assets_dir.exists()){
        qDebug() << "Directory .svn not found";
        install.on_buttonBox_accepted();

    }
    else {
        qDebug() << "SVN directory detected";
        setCheckerParam("Main/LocalRev",QString::number(svnLocalInfo()));
        w.show();
    }

    return a.exec();
}


