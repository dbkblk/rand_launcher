#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_5_clicked();

    void on_actionForum_triggered();

    void on_actionAddon_Mega_Civ_Pack_triggered();

    void on_actionBugreport_triggered();

    void on_actionAbout_AND_Resurrection_team_forum_triggered();

    void on_actionExit_triggered();

    void on_autostartButton_clicked();

    void on_pushButton_4_clicked();

    void on_updateButton_clicked();

    void on_revertButton_clicked();

    void on_cleanupButton_clicked();

    void on_colorBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
