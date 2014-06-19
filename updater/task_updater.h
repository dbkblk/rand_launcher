#ifndef TASK_UPDATER_H
#define TASK_UPDATER_H

#include <QMainWindow>
#include <QtCore>

namespace Ui {
class task_updater;
}

class task_updater : public QMainWindow
{
    Q_OBJECT

public:
    explicit task_updater(QWidget *parent = 0);
    ~task_updater();
    QString svn_update(int current_revision, int output_revision);
    void initialize();
    void execute(QString command);
    void appendText(QString text);
    void addonInstaller(QString name, QString link);

signals:
    void finished();

public slots:
    void appendOutput();
    void executeFinished();
    void executeError(QProcess::ProcessError);
    void restartLauncher();

private:
    Ui::task_updater *ui;
    QProcess svn;
    QProcess process;
    QTimer process_timer;
    QString process_file;
    qint64 process_file_pos;
    int progress;
};

#endif // TASK_UPDATER_H
