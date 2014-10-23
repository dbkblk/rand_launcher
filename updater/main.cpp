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

    w->show();
    //w->sync();

    return a.exec();
}
