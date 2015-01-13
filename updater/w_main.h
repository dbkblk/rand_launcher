#ifndef w_main_H
#define w_main_H

#include <QMainWindow>
#include <QtCore>
#include "f_updater.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QThread>

namespace Ui {
class w_main;
}

namespace tools {
// Define OS tools
#ifdef __linux
const QString TOOL_RSYNC = "rsync ";
const QString TOOL_GET = "curl -J -L -C - -# --retry 10 --insecure ";
const QString TOOL_EXTRACT = "7z e ";
const QString TOOL_LAUNCHER = "and2_checker";
const QString TOOL_UPDATER = "upd_proc";
#endif
#ifdef _WIN32
const QString TOOL_RSYNC = "rsync.exe ";
const QString TOOL_GET = "checker/curl.exe -J -L -C - -# --retry 10 --insecure ";
const QString TOOL_EXTRACT = "checker/7za.exe e ";
const QString TOOL_LAUNCHER = "and2_checker.exe";
const QString TOOL_UPDATER = "upd_proc.exe";
#endif
}

class w_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit w_main(QWidget *parent = 0);
    ~w_main();
    void StartUpdate();
    void DebugWindow(int time);
    QString ReadExcludeList(QString filepath);
    QString readCheckerParam(QString param);
    void ResetInstallation();

public slots:
    void restartLauncher();
    void errorPopup();
    void updateInterface(int percent, int value);

private:
    Ui::w_main *ui;
    QThread *thread;
    f_updater *worker;
    QTranslator *translator;
};

#endif // w_main_H
