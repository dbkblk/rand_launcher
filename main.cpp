#include "mainwindow.h"
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFileDialog>

using namespace std;

int main(int argc, char *argv[])
{
    // Start the GUI
    QApplication a(argc, argv);
    MainWindow w;
    installBox install;

    // Check for installation -> Remember to connect the two signals.

    if (!dirExists(".svn")) {
        qDebug() << "Directory .svn not found";
        install.show();
    }

    else {
        qDebug() << "Else passed";
        const char* exelocation = readXML("version.xml","exelocation");
        qDebug() << exelocation;
        if(exelocation = "0") {
            QWidget
            qDebug() << "Pas d'exe";
            exelocation = QFileDialog::getOpenFileName(install);

        }
        w.show();
    }



    // Please locate your Civ IV Executable -> Store in xml file



    return a.exec();
}


