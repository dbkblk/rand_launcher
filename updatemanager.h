#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "updatebox.h"
#include <QWidget>
#include <QCheckBox>
#include <QObject>
#include <QMutex>
#include <QSettings>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>

namespace Ui {
class updateManager;
}

bool clearCache();
bool clearGameOptions();
bool launcherUpdate();
int svnLocalInfo();
int svnDistantInfo();

class updateManager : public QWidget
{
    Q_OBJECT

public:
    explicit updateManager(QWidget *parent = 0);
    ~updateManager();

public slots:
    void updateDistantInfos();
    void changelogCore();
    void on_launcher_changelog_clicked();
    void on_addon_sogroon_clicked();
    void on_addon_megacivpack_clicked();
    void addons_installation();

private:
    QTableWidget *tab_updates;
    QTableWidgetItem *item_distant_vers;
    QTableWidgetItem *item_distant_launcher;
    QTableWidgetItem *item_distant_addon_MCP;
    QTableWidgetItem *item_distant_addon_MoreMusic;
    QTableWidgetItem *item_distant_addon_MoreHandicaps;
    QPushButton apply;
    QPushButton cancel;
    updatebox *changelog_box;
    updatebox *addon_setup;
    QCheckBox *update_core_checkbox;
    QCheckBox *update_launcher_checkbox;
    QCheckBox *update_addon_MCP_checkbox;
    QCheckBox *update_addon_moremusic_checkbox;
    QCheckBox *update_addon_morehandicaps_checkbox;
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

    void UMCheckUpdate();
};

class Addons : public QWidget
{
        Q_OBJECT

public:
    explicit Addons(QWidget *parent = 0);
    ~Addons();
    void WindowInstaller();

public slots:


private:
    updatebox *addon_setup;
    QCheckBox *addon_mega_civ_pack;
    QCheckBox *addon_more_music;
    QCheckBox *addon_more_handicaps;
    QSettings *box_state;
    QPushButton *addon_close;
    QPushButton *addon_apply;
};

#endif // UPDATEMANAGER_H
