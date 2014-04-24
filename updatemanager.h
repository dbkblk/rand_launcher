#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QWidget>

namespace Ui {
class updateManager;
}

class updateManager : public QWidget
{
    Q_OBJECT

public:
    explicit updateManager(QWidget *parent = 0);
    ~updateManager();

private:
    Ui::updateManager *ui;
};

#endif // UPDATEMANAGER_H
