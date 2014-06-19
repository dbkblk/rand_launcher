#ifndef MODULES_H
#define MODULES_H

#include <QMainWindow>
#include <QtCore>
#include <QTreeWidgetItem>

namespace Ui {
class modules;
}

class modules : public QMainWindow
{
    Q_OBJECT

public:
    explicit modules(QWidget *parent = 0);
    ~modules();

private slots:
    void on_tree_list_itemClicked(QTreeWidgetItem *item);
    void moduleInterface(QString version, QString description);

private:
    Ui::modules *ui;
    QProcess process;
    QTimer process_timer;
    QString process_file;
    qint64 process_file_pos;
    QTreeWidgetItem *core;
    QTreeWidgetItem *addons;
    QTreeWidgetItem *add_blue_marble;
    QTreeWidgetItem *add_mega_civ_pack;
    QTreeWidgetItem *add_more_music;
    QTreeWidgetItem *add_more_handicaps;
    QTreeWidgetItem *add_dinosaurs;
};

#endif // MODULES_H
