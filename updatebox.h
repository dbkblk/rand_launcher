#ifndef UPDATEBOX_H
#define UPDATEBOX_H

#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QProcess>
#include <QTimer>
#include <QProcess>
#include <QPushButton>

namespace Ui {
class updatebox;
}

class updatebox : public QMainWindow
{
    Q_OBJECT

public:
    explicit updatebox(QWidget *parent = 0);
    ~updatebox();
    void execute(QString command, bool &cursorUp);
    void changelogMode();

private slots:
    void executeFinished();
    void executeError(QProcess::ProcessError);
    void appendOutput();


private:
    Ui::updatebox *ui;
    QTextEdit* consoleOutput;
    bool* cursorUp;
    QPushButton* bt_chglog_close;
    QProcess process;
    QTimer process_timer;
    QString process_file;
    qint64 process_file_pos;
};

#endif // UPDATEBOX_H
