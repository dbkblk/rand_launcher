#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include <QWidget>

namespace Ui {
class optionBox;
}

class optionBox : public QWidget
{
    Q_OBJECT

public:
    explicit optionBox(QWidget *parent = 0);
    ~optionBox();

private slots:
    void on_opt_bt_update_clicked();

    void on_opt_bt_cleanup_clicked();

    void on_opt_bt_restore_clicked();

    void on_opt_bt_chooserev_clicked();

private:
    Ui::optionBox *ui;
};

#endif // OPTIONBOX_H
