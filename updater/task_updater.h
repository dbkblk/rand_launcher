#ifndef TASK_UPDATER_H
#define TASK_UPDATER_H

#include <QMainWindow>
#include <QtCore>

namespace Ui {
class task_updater;
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

class task_updater : public QMainWindow
{
    Q_OBJECT

public:
    explicit task_updater(QWidget *parent = 0);
    ~task_updater();
    void StartUpdate(QString operation);
    void DebugWindow(int time);
    QString ReadExcludeList(QString filepath);
    QString readCheckerParam(QString param);

signals:
    void finished();
    void stopUpdate();
    void error();

public slots:
    void processOutput();
    void StopGUI();
    void restartLauncher();
    void errorPopup();

private:
    Ui::task_updater *ui;
    QProcess* process;
    QTranslator *translator;
};

#endif // TASK_UPDATER_H
