#ifndef W_EXCLUSION_H
#define W_EXCLUSION_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>

namespace Ui {
class w_exclusion;
}

class w_exclusion : public QDialog
{
    Q_OBJECT

public:
    explicit w_exclusion(QWidget *parent = 0);
    QStringList ListFiles();
    void PopulateList(QTreeWidget *treeWidget, QStringList file_list, QStringList exclusion_list);
    void CheckChildState(QTreeWidgetItem* item, enum Qt::CheckState eCheckState);
    void ValidateParentState(QTreeWidgetItem* item);
    QStringList ReadExcludedList(QString filepath);
    void WriteToXML(QStringList file_list);
    QStringList GetCheckedList();
    ~w_exclusion();

public slots:
        void modeItemChecked(QTreeWidgetItem * item, int nColumn );
        void GetOutputList();

private:
    Ui::w_exclusion *ui;
    QTreeWidget* treeWidget;
    QTreeWidgetItem *topLevelItem;
};

#endif // W_EXCLUSION_H
