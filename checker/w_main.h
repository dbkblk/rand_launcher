#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <w_options.h>
#include <w_modules.h>
#include <f_check.h>
#include <f_mods.h>

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QThread>

namespace Ui {
class w_main;
class installBox;
}

namespace versions {
const QString CHECKER_VERSION = "1.09";
}

namespace tools {
// Define OS tools
#ifdef __linux
const QString TOOL_RSYNC = "rsync ";
const QString TOOL_GET = "curl -J -L -C - -# --retry 10 --insecure ";
const QString TOOL_XZ = "xz -d ";
const QString TOOL_TAR = "tar -xpf ";
const QString TOOL_LAUNCHER = "and2_checker";
const QString TOOL_UPDATER = "upd_proc";
#endif
#ifdef _WIN32
const QString TOOL_RSYNC = "checker/rsync.exe ";
const QString TOOL_GET = "checker/curl.exe -J -L -C - -# --retry 10 --insecure ";
const QString TOOL_XZ = "checker/xz.exe -d ";
const QString TOOL_TAR = "checker/tar.exe -xpf ";
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
    QWidget *updateGUI;

public slots:
    void stopLauncher();
    void openURL(QString url);

private slots:
    void on_actionForum_triggered();
    void on_actionBugreport_triggered();
    void on_actionAbout_AND_Resurrection_team_forum_triggered();
    void on_actionExit_triggered();
    void on_bt_launch_clicked();
    void on_bt_option_clicked();
    void UpdateWindowInfos();
    void on_actionOpen_mod_folder_triggered();
    void UpdateAvailable(bool update);
    void RestoreButtonState();
    void on_bt_components_clicked();
    void on_actionHelp_translate_the_mod_triggered();
    void on_actionTranslate_the_mod_help_triggered();
    void on_actionTranslate_the_civilopedia_triggered();
    void clear_language_state();
    void on_language_en_triggered();
    void on_language_fr_triggered();
    void on_language_hu_triggered();
    void on_language_fi_triggered();
    void on_language_it_triggered();
    void on_language_es_triggered();
    void on_language_de_triggered();
    void on_language_ru_triggered();
    void on_language_pl_triggered();
    void on_actionClear_cache_triggered();
    void on_actionReset_triggered();
    void on_actionWebsite_triggered();
    void on_language_cs_triggered();
    void on_language_da_triggered();
    void on_language_ar_triggered();
    void on_language_tr_triggered();
    void language_select(QString langCode);
    void populate_language_menu(QString code);
    void populate_mod_list();
    void setModStatus(QString mod_name);

    void on_actionGive_us_feedback_forum_triggered();

    void on_actionTranslate_the_website_triggered();

    void on_actionTranslate_the_module_Mega_Civ_pack_triggered();

private:
    Ui::w_main *ui;
    w_options *options;
    QMap<QAction *, QString> action_mod;
    QThread *thread;
    f_check *worker;
    QThread *inj_thread;
    f_injection *inj_worker;
    QMessageBox askUpdate;
    QTranslator *translator;
    w_modules *modules;
};

#endif // MAINWINDOW_H
