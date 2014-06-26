#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include <updatebox.h>

namespace Ui {
class w_options;
}

class w_options : public QMainWindow
{
    Q_OBJECT

public:
    explicit w_options(QWidget *parent = 0);
    ~w_options();
    void reTranslate();

private slots:
    void on_colorBox_currentIndexChanged(int index);
    void on_startBox_toggled(bool checked);
    void on_checkerBox_toggled(bool checked);
    void on_opt_bt_path_clicked();
    void on_opt_checkbox_formations_toggled(bool checked);
    void on_opt_checkbox_bluemarble_toggled(bool checked);
    void on_opt_updateBehavior_currentIndexChanged(int index);

private:
    QCheckBox *startBox;
    QCheckBox *checkerBox;
    QLineEdit *opt_text_path;
    Ui::w_options *ui;
};

#endif // OPTIONBOX_H