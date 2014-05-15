#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "updatebox.h"
#include <QWidget>
#include <QCheckBox>
#include <QObject>
#include <QMutex>

namespace Ui {
class updateManager;
}

bool clearCache();
bool launcherUpdate();
int svnLocalInfo();
int svnDistantInfo();

class updateManager : public QWidget
{
    Q_OBJECT

public:
    explicit updateManager(QWidget *parent = 0);
    ~updateManager();

private:
    Ui::updateManager *ui;
};

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0);
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();
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

    void UMCheckLauncherUpdate();
};

class Addons : public QWidget
{
        Q_OBJECT

public:
    explicit Addons(QWidget *parent = 0);
    ~Addons();
    void WindowInstaller();

public slots:
    void addons_installation();

private:
    updatebox *addon_setup;
    QCheckBox *addon_civ_mega_pack;
    QCheckBox *addon_more_music;
};

#endif // UPDATEMANAGER_H
