#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <updatebox.h>
#include <optionbox.h>
#include <QThread>
#include "updatemanager.h"
#include "modules.h"

namespace Ui {
class MainWindow;
class installBox;
}

namespace constants {
const int MAJOR_CHECKER_VERSION = 0;
const int MINOR_CHECKER_VERSION = 11;

// Define the update url (the second is for testing purpose)
const QString GLOBAL_UPDATE_URL = "checker/curl.exe -o checker/update.ini -J -L -C - -# --retry 10 --insecure https://raw.githubusercontent.com/dbkblk/and2_checker/master/update.ini";
//const QString GLOBAL_UPDATE_URL = "checker/curl.exe -o checker/update.ini -J -L -C - -# --retry 10 --insecure https://dl.dropboxusercontent.com/u/369241/update.ini";
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget *updateGUI;

private slots:

    void on_actionForum_triggered();
    void on_actionAddon_Mega_Civ_Pack_triggered();
    void on_actionBugreport_triggered();
    void on_actionAbout_AND_Resurrection_team_forum_triggered();
    void on_actionExit_triggered();
    void on_actionAddon_More_music_forum_triggered();
    void on_bt_launch_clicked();
    void on_bt_update_clicked();
    void on_bt_option_clicked();
    void UpdateWindowInfos();
    void on_actionOpen_mod_folder_triggered();
    void UpdateAvailable(bool update);
    void RestoreButtonState();
    void on_bt_components_clicked();
    void on_actionGit_Pack_binaries_triggered();
    void on_actionGit_Create_update_binary_pack_triggered();
    void on_actionHelp_translate_the_mod_triggered();
    void on_actionTranslate_the_mod_help_triggered();
    void on_actionTranslate_the_launcher_triggered();
    void on_languageEnglish_triggered();
    void on_languageFrench_triggered();
    void on_languageSinhala_triggered();

    void on_languageHungarian_triggered();

    void on_languageFinnish_triggered();

    void on_languageItalian_triggered();

    void on_languageSpanish_triggered();

    void on_languageGerman_triggered();

    void on_languageRussian_triggered();

    void on_actionClean_up_triggered();

    void on_actionRevert_to_an_older_revision_triggered();

    void on_actionAddon_Blue_marble_triggered();

private:
    Ui::MainWindow *ui;
    updatebox *ubox;
    optionBox *optbox;
    QThread *thread;
    Worker *worker;
    QMessageBox askUpdate;
    updateManager *update_manager;
    QTranslator *translator;
    modules *manager;
};

class installBox : public QDialog {

    Q_OBJECT

public :
    explicit installBox(QDialog *parent = 0);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::installBox *ui;
    updatebox *inst_view;

};

#endif // MAINWINDOW_H
