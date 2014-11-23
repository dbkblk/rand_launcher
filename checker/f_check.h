#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QWidget>
#include <QComboBox>
#include <QObject>
#include <QMutex>
#include <QSettings>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QEventLoop>

namespace Ui {
class updateManager;
class svn_functions;
}

class f_check : public QObject
{
    Q_OBJECT

public:
    explicit f_check(QObject *parent = 0);
    void requestWork();
    bool AddonsVersionCalculation();
    bool LauncherVersionCalculation();
    bool ActionLauncherUpdate();
    bool PrepareUpdate();
    bool ActionUpdate();
    int GetLocalVersion();
    int GetDistantVersion();
    QString ExtractChangelog(QString filepath);
    void abort();

private:
    bool _abort;
    bool _working;
    QMutex mutex;

signals:
    void workRequested();
    void finished(bool update);
    bool work_update_check(bool update);

public slots:
    void CheckForUpdate();
};

#endif // UPDATEMANAGER_H
