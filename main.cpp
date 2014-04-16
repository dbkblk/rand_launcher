#include "mainwindow.h"
#include <QApplication>
#include <QComboBox>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <wchar.h>
#include <civ_functions.h>
#include <lib\tinyxml2.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Start the GUI
    QApplication a(argc, argv);
    MainWindow w;

    // Initial parameters
    // Check for installation
    checkInstall();

    w.show();

    return a.exec();
}


