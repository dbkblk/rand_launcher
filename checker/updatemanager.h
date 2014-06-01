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
}

bool clearCache();
bool clearGameOptions();
bool ActionLauncherUpdate();
void restartLauncher();
bool LauncherVersionCalculation();
bool AddonsVersionCalculation();
int svnLocalInfo();
int svnDistantInfo();

class updateManager : public QWidget
{
    Q_OBJECT

public:
    explicit updateManager(QWidget *parent = 0);
    ~updateManager();

signals:
    void components_installed();

public slots:
    void updateInfos();
    void changelogCore();
    void on_launcher_changelog_clicked();
    void on_addon_sogroon_clicked();
    void on_addon_megacivpack_clicked();
    void ProcessActions();
    void CheckComboBoxState();
    void ActionCoreUpdate();
    void ActionCoreRevert();
    void ActionCoreClean();
    void ActionAddonMCPUpdate();
    void ActionAddonMCPRemove();
    void ActionAddonMoreMusicUpdate();
    void ActionAddonMoreMusicRemove();
    void ActionAddonMoreHandicapsUpdate();
    void ActionAddonMoreHandicapsRemove();

private:
    QTableWidget *tab_updates;
    QTableWidgetItem *item_local_vers = new QTableWidgetItem;
    QTableWidgetItem *item_local_launcher = new QTableWidgetItem;
    QTableWidgetItem *item_local_addon_MCP = new QTableWidgetItem;
    QTableWidgetItem *item_local_addon_MoreMusic = new QTableWidgetItem;
    QTableWidgetItem *item_local_addon_MoreHandicaps = new QTableWidgetItem;
    QTableWidgetItem *item_distant_vers = new QTableWidgetItem;
    QTableWidgetItem *item_distant_launcher = new QTableWidgetItem;
    QTableWidgetItem *item_distant_addon_MCP = new QTableWidgetItem;
    QTableWidgetItem *item_distant_addon_MoreMusic = new QTableWidgetItem;
    QTableWidgetItem *item_distant_addon_MoreHandicaps = new QTableWidgetItem;
    QPushButton *apply = new QPushButton(this);
    QPushButton *cancel = new QPushButton(this);
    updatebox *changelog_box;
    updatebox *apply_setup;
    QComboBox *update_core_combobox;
    QComboBox *update_launcher_combobox;
    QComboBox *update_addon_MCP_combobox;
    QComboBox *update_addon_moremusic_combobox;
    QComboBox *update_addon_morehandicaps_combobox;
    QWidget *update_core_widget = new QWidget;
    QWidget *update_launcher_widget = new QWidget;
    QWidget *update_addon_MCP_widget = new QWidget;
    QWidget *update_addon_moremusic_widget = new QWidget;
    QWidget *update_addon_morehandicaps_widget = new QWidget;
    QEventLoop wait_install;
    QEventLoop wait_svn;
    QTimer wait_timer;

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

#endif // UPDATEMANAGER_H
