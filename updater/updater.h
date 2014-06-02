#ifndef UPDATER_H
#define UPDATER_H

#include <QMainWindow>
#include <QLabel>
#include <QProcess>
#include <QThread>
#include <QMutex>

class process : public QWidget
{
    Q_OBJECT

public:
    void KillProcess();
    void Download(QString link);
    void Extraction();
    void Finalization();

signals:
    void finished();

private:
    QProcess *tasks = new QProcess();

};

class updater : public QMainWindow
{
    Q_OBJECT

public:
    updater(QWidget *parent = 0);
    ~updater();
    void exit();
    void Execute(QString link);

private:
    QLabel *central = new QLabel();
    process *proc = new process();

};

#endif // UPDATER_H
