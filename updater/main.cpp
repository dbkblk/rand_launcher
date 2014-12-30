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
    w.DebugWindow(3000);

    if(argc > 1)
    {
        QString arg1 = argv[1];
        if(arg1 == "reset")
        {
                QFile temp("reset");
                temp.open(QIODevice::WriteOnly | QIODevice::Truncate);
                temp.close();
                QString operation = tools::TOOL_RSYNC + QString("-rz --info=progress2 --delete-after --exclude=\"cyggcc_s-1.dll\" --exclude=\"cygiconv-2.dll\" --exclude=\"cygwin1.dll\" --exclude=\"rsync.exe\" --exclude=\"upd_proc.exe\" --exclude=\".svn*\" --exclude=\"updating\" afforess.com::ftp/ .");
                w.StartUpdate(operation);
        }
        else{
            qDebug() << "Unknown argument";
        }
    }
    else{
        // Write temp file
        QFile temp("updating");
        temp.open(QIODevice::WriteOnly | QIODevice::Truncate);
        temp.close();

        // Check exclusion file
        QString exclusion_default = w.ReadExcludeList("checker/exclusions.default.xml");
        QString exclusion_custom = w.ReadExcludeList("checker/exclusions.custom.xml");

        // Initialize update
        QString operation = tools::TOOL_RSYNC + QString("-rz --info=progress2 --delete-after %1%2rsync://afforess.com/ftp/ .").arg(exclusion_default).arg(exclusion_custom);
        qDebug() << operation;

        // Execute update operation
        w.StartUpdate(operation);
    }
    return 0;
}
