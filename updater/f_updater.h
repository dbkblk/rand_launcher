#ifndef F_UPDATER_H
#define F_UPDATER_H
#include "QtCore"

class f_updater : public QObject
{
    Q_OBJECT

public:
    explicit f_updater(QObject *parent = 0);
    void requestWork();
    void abort();
    QString readExcludeList(QString filepath);

signals:
    void finished();
    void workRequested();
    void progress(int percent, int files_left);
    void stopUpdate();
    void error();

public slots:
    void updateLaunch();
    void resetLaunch();
    void processOutput();

private:
    bool _abort;
    bool _working;
    QMutex mutex;
    QProcess* process;
};

#endif // F_UPDATER_H
