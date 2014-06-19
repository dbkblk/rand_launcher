#include "updater.h"
#include "task_updater.h"
#include "QCoreApplication"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    task_updater *w = new task_updater();

    if(argc == 3)
    {
        QString arg1 = argv[1];
        QString arg2 = argv[2];
        if(arg1 == "update" && arg2.toInt() > 0)
        {
            w->show();
            w->svn_update(arg2.toInt());
        }
    }

    return a.exec();
}
