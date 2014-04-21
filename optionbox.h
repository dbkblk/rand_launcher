#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include <QWidget>
#include <QCheckBox>

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

    void on_colorBox_currentIndexChanged(const QString &colorName);

    void on_startBox_toggled(bool checked);

    void on_checkerBox_toggled(bool checked);

private:
    QCheckBox *startBox = new QCheckBox;
    QCheckBox *checkerBox = new QCheckBox;
    Ui::optionBox *ui;
};

#endif // OPTIONBOX_H
