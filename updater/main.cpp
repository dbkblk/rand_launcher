#include "updater.h"
#include "QCoreApplication"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QEventLoop>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    updater *w = new updater();

    QString link;

    if (argc == 2)
    {
        link = argv[2];
    }
    w->Execute("https://dl.dropboxusercontent.com/u/369241/AND2_CHECKER_V0.9.7z");
    w->show();

    return a.exec();
}
