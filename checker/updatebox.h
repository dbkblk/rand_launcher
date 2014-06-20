#ifndef UPDATEBOX_H
#define UPDATEBOX_H

#include "f_svn.h"

#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QProcess>
#include <QTimer>
#include <QProcess>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>

namespace Ui {
class updatebox;
}

class updatebox : public QMainWindow
{
    Q_OBJECT

public:
    explicit updatebox(QWidget *parent = 0);
    ~updatebox();
    void execute(QString command);
    void appendText(QString text);
    void changelogMode();
    void updateMode();
    void installMode();
    void addonsMode();
    bool updateLauncherGUI();
    QPushButton* bt_chglog_close;
    QLabel* lb_changelog;
    QLabel* lb_addons;
    QString message;
    QTextEdit* consoleOutput;


private slots:
    void executeFinished();
    void executeError(QProcess::ProcessError);
    void appendOutput();
    void on_bt_update_accepted();
    void on_bt_update_rejected();

signals:
    void finished();
    void updated();

private:
    Ui::updatebox *ui;
    QProcess process;
    QTimer process_timer;
    QString process_file;
    qint64 process_file_pos;
};

#endif // UPDATEBOX_H
