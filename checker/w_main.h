#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <w_options.h>
#include <w_modules.h>
#include <f_check.h>

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <QThread>

namespace Ui {
class w_main;
class installBox;
}

namespace constants {
const int MAJOR_CHECKER_VERSION = 0;
const int MINOR_CHECKER_VERSION = 15;

// Define the update url (the second is for testing purpose)
const QString GLOBAL_UPDATE_URL = "checker/curl.exe -o checker/update.ini -J -L -C - -# --retry 10 --insecure https://raw.githubusercontent.com/dbkblk/and2_checker/master/update.ini";
//const QString GLOBAL_UPDATE_URL = "checker/curl.exe -o checker/update.ini -J -L -C - -# --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/update.ini";
}

class w_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit w_main(QWidget *parent = 0);
    ~w_main();
    QWidget *updateGUI;

private slots:

    void on_actionForum_triggered();
    void on_actionAddon_Mega_Civ_Pack_triggered();
    void on_actionBugreport_triggered();
    void on_actionAbout_AND_Resurrection_team_forum_triggered();
    void on_actionExit_triggered();
    void on_actionAddon_More_music_forum_triggered();
    void on_bt_launch_clicked();
    void on_bt_option_clicked();
    void UpdateWindowInfos();
    void on_actionOpen_mod_folder_triggered();
    void UpdateAvailable(bool update);
    void RestoreButtonState();
    void on_bt_components_clicked();
    void on_actionHelp_translate_the_mod_triggered();
    void on_actionTranslate_the_mod_help_triggered();
    void on_actionTranslate_the_launcher_triggered();
    void clear_language_state();
    void on_language_en_triggered();
    void on_language_fr_triggered();
    void on_language_si_triggered();
    void on_language_hu_triggered();
    void on_language_fi_triggered();
    void on_language_it_triggered();
    void on_language_es_triggered();
    void on_language_de_triggered();
    void on_language_ru_triggered();
    void on_language_pl_triggered();
    void on_actionAddon_Blue_marble_triggered();
    void on_actionClear_cache_triggered();

private:
    Ui::w_main *ui;
    w_options *options;
    QThread *thread;
    f_check *worker;
    QMessageBox askUpdate;
    QTranslator *translator;
    w_modules *modules;
};

#endif // MAINWINDOW_H
