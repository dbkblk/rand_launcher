#include "mainwindow.h"
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QApplication>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    // Start the GUI
    QApplication a(argc, argv);
    MainWindow w;
    installBox install;

    // Check for installation -> Remember to connect the two signals.

    if (!dirExists(".svn")) {
        qDebug() << "Directory .svn not found" << endl;
        install.show();
    }

    else {
        w.show();
    }



    // Please locate your Civ IV Executable -> Store in xml file



    return a.exec();
}


