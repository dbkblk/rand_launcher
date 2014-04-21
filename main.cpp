#include "mainwindow.h"
#include "optionbox.h"
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

using namespace std;

int main(int argc, char *argv[])
{
    // Start the GUI
    QApplication a(argc, argv);
    MainWindow w;
    installBox install;

    // Set version in ini file
    QString checker_version = "0.5";
    setCheckerParam("MAIN/CheckerVersion",checker_version);

    // Check for correct path
    QDir BTS_dir("../../../Beyond the sword");
    if(!BTS_dir.exists()){
        qDebug() << "Launcher is in a wrong path";
        QMessageBox::critical(0, "Error", "The launcher isn't in the right directory. Please unzip the file to ""My Documents/My Games/Beyond the Sword/Mods/"" and launch it again");
        return 1;
    }

    // Check for installation -> Remember to connect the two signals.
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


