#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>

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

private:
    Ui::MainWindow *ui;
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

};

class Downloader : public QObject
{
    Q_OBJECT

public:
    Downloader(void);
    ~Downloader(void);

    QString download(QString in_url, QString in_output);

public slots:
    void replyFinished(QNetworkReply *r, QString in_output);

private:
    QNetworkAccessManager   *manager;
};

#endif // MAINWINDOW_H
