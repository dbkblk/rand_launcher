#include "updater.h"
#include "QCoreApplication"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    updater *w = new updater();

    QString link;

    if (argc == 2)
    {
        link = argv[2];
        qDebug() << link;
    }
    w->Execute(link);
    w->show();

    return a.exec();
}
