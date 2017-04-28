#include "w_main.h"
#include "QCoreApplication"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <iostream>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    // Create the application
    QApplication a(argc, argv);
    w_main *w = new w_main;
    w->show();
    //w.DebugWindow(3000);

    // Arguments
    if(argc > 1)
    {
        QString arg1 = argv[1];
        if(arg1 == "reset")
        {
                w->ResetInstallation();
        }
        else{
            qDebug() << "Unknown argument";
        }
    }
    else{
    // Start the updater using the standard routine
        w->StartUpdate();
    }

    return a.exec();
}
