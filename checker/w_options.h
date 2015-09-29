#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>
#include "w_exclusion.h"

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
    void on_bt_exclusions_clicked();
    void on_dd_textures_currentIndexChanged(int index);
    void populateColorBox();
    void on_bt_customColor_clicked();
    void on_opt_checkbox_modern_flags_toggled(bool checked);

    void on_opt_checkbox_disable_warning_toggled(bool checked);

private:
    QCheckBox *startBox;
    QCheckBox *checkerBox;
    QLineEdit *opt_text_path;
    Ui::w_options *ui;
    w_exclusion *exclusion;
    int init;
};

#endif // OPTIONBOX_H
