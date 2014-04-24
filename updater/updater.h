#ifndef UPDATER_H
#define UPDATER_H

#include <QMainWindow>
#include <QLabel>
#include <QProcess>

class updater : public QMainWindow
{
    Q_OBJECT

public:
    updater(QWidget *parent = 0);
    ~updater();
    void exit();

private:
    QLabel *central;
    QProcess *tasks;
};

#endif // UPDATER_H
