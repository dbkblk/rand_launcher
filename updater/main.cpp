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
    w->DebugWindow();

    // Loop process to allow retrying
    int loop = 0;
    while (loop != 1){
        // Count total files and check for errors
        if(w->CountFiles() == -1){
            qDebug() << "An error has occured";

            // Invoke a retry dialog box
            QMessageBox retry;
            retry.setWindowTitle("Update");
            retry.setText("The update has failed");
            retry.setInformativeText("Do you want to retry ?");
            retry.setStandardButtons(QMessageBox::Yes |QMessageBox::No);
            retry.setDefaultButton(QMessageBox::Yes);
            int ret = retry.exec();

            switch (ret) {
              case QMessageBox::Yes:
                  break;
              case QMessageBox::No:
                  loop = 1;
                  break;

              default:
                  break;
            }
        }
        else {
            // Check exclusion file

            QString exclusion = "--exclude \".svn*\"";

            // Initialize update
            QString operation = tools::TOOL_RSYNC + QString("-vvrz --delete-after %1 afforess.com::ftp/ .").arg(exclusion);
            qDebug() << operation;
            w->initialize();

            // Execute update operation
            w->execute(operation);
            loop = 1;
        }
    }

    return a.exec();
}
