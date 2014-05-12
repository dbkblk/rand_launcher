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

namespace Ui {
class MainWindow;
class installBox;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget *updateGUI;
    QMessageBox *ask_update;



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
    void UpdateAvailable(bool update);
    void UpdateWindowInfos();

    void on_actionOpen_mod_folder_triggered();

private:
    Ui::MainWindow *ui;
    updatebox *ubox;
    optionBox *optbox;
    QThread *thread;
    Worker *worker;
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
