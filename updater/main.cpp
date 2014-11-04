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
    task_updater w;
    w.show();
    w.DebugWindow();

    // Check exclusion file
    QString exclusion = w.ReadExcludeList();

    // Initialize update
    QString operation = tools::TOOL_RSYNC + QString("-rz --info=progress2 --delete-after %1afforess.com::ftp/ .").arg(exclusion);
    qDebug() << operation;

    // Execute update operation
    w.StartUpdate(operation);

    return 0;
}
