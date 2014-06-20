#include "task_updater.h"
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
    QApplication a(argc, argv);
    task_updater *w = new task_updater();

    if(argc > 1)
    {
        QString arg1 = argv[1];
        QString arg2 = argv[2];
        QString arg3 = argv[3];
        if(arg1 == "update" && arg2.toInt() > 0)
        {
            w->show();
            if(arg3.toInt() > 0)
            {
                w->svn_update(arg2.toInt(), arg3.toInt());
            }
            else
            {
                w->svn_update(arg2.toInt(), 0);
            }
        }
        else if(arg1 == "install")
        {
            w->show();
            w->svn_install();
        }
    }

    return a.exec();
}
