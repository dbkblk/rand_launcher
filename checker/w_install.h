#ifndef W_INSTALL_H
#define W_INSTALL_H

#include "ui_w_install.h"
#include <QtCore>
#include <QtWidgets>

void restartLauncher();

class w_install : public QDialog {

    Q_OBJECT

public :
    explicit w_install(QDialog *parent = 0);

public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::w_install *ui;
};

#endif // W_INSTALL_H
