#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "updatebox.h"

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
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();
    bool AddonsVersionCalculation();
    bool LauncherVersionCalculation();
    bool ActionLauncherUpdate();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abort();

private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;

signals:
    void workRequested();
    void finished(bool update);
    bool work_update_check(bool update);

public slots:

    void UMCheckUpdate();

};

#endif // UPDATEMANAGER_H
