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
                QString operation = tools::TOOL_RSYNC + QString("-rz --info=progress2 --delete-after --exclude \"cygcrypto-1.0.0.dll\" --exclude \"cyggcc_s-1.dll\" --exclude \"cygiconv-2.dll\" --exclude \"cygssp-0.dll\" --exclude \"cygwin1.dll\" --exclude \"cygz.dll\" --exclude \"rsync.exe\" --exclude \"upd_proc.exe\" --exclude \".svn*\" --exclude \"updating\" afforess.com::ftp/ .");
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
        QString exclusion = w.ReadExcludeList("checker/exclusions.default.xml");
        QString exclusion_custom = w.ReadExcludeList("checker/exclusions.custom.xml");

        // Initialize update
        QString operation = tools::TOOL_RSYNC + QString("-rz --info=progress2 --delete-after %1%2afforess.com::ftp/ .").arg(exclusion).arg(exclusion_custom);
        //operation.replace("\"","\\\"");
        qDebug() << operation;

        // Execute update operation
        w.StartUpdate(operation);
    }
    return 0;
}
