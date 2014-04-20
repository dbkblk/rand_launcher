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

            // Check executable location if it doesn't exist

        if(readXML("version.xml","exelocation") == NULL) {
            qDebug() << "Pas d'exe";
            QMessageBox::information(0, "Information", "To be able to launch the game from the launcher, it need to know where the executable is located. The next window will ask you to select your Civ. IV Beyond the Sword executable");
            QString exeloc = QFileDialog::getOpenFileName(0, "Find Civ. IV executable", QString(), "Executable (*.exe)");
            qDebug() << exeloc;
            writeXML("version.xml","exelocation",exeloc.toStdString().c_str());
            w.show();
        }

        // If the SVN folder and exe location are registred, go straight to the menu

        else
        w.show();
    }







    return a.exec();
}


