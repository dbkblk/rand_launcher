#include "mainwindow.h"
#include "optionbox.h"
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QDir>

using namespace std;

int main(int argc, char *argv[])
{
    // Start the GUI
    QApplication a(argc, argv);
    MainWindow w;
    installBox install;

    // Set version in ini file
    QString checker_version = "0.8";
    setCheckerParam("MAIN/CheckerVersion",checker_version);

    // Cleanup update output
    QFile update_output("update_out.ini");
    if(update_output.exists()) {
        QProcess::startDetached("taskkill /f /im upd_proc.exe");
        update_output.remove();
        QDir temp("temp");
        temp.rmdir("temp");
    }

    // Check for correct path
    QDir BTS_dir("../../../Beyond the sword");
    if(!BTS_dir.exists()){
        qDebug() << "Launcher is in a wrong path";
        QMessageBox::critical(0, "Error", "The launcher isn't in the right directory. Please reinstall the application and launch it again");
        return 1;
    }

    // Check for installation
    QDir svn_dir(".svn");
    if(!svn_dir.exists()){
        qDebug() << "Directory .svn not found";
        install.show();

    }
    else {
        qDebug() << "SVN directory detected";
        w.show();
        //launcherCheck();
    }

    return a.exec();
}


