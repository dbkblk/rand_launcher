#include "mainwindow.h"
#include "optionbox.h"
#include <civ_functions.h>
#include <lib\tinyxml2.h>
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

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
        w.show();
    }

    return a.exec();
}


