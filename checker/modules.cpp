#include "modules.h"
#include "ui_modules.h"
#include "updatemanager.h"
#include "svn_functions.h"
#include "civ_functions.h"
#include <QtCore>

modules::modules(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modules)
{
    ui->setupUi(this);

    // Set version label
    ui->label_core_version->setText(QString("Version:\n%1").arg(svnLocalInfo()));
    ui->changelog_box->setText(svnGetChangelog(10));
    ui->bt_remove->hide();
    ui->bt_update->hide();
    if(readCheckerParam("Main/LocalRev").toInt() < readCheckerParam("Update/DistantRev").toInt())
    {
        ui->bt_update->setText(tr("Update:") + "\n" + readCheckerParam("Update/DistantRev"));
        ui->bt_update->show();
    }

    // Set the TreeWidget items
    core = new QTreeWidgetItem(ui->tree_list);
    core->setText(0, tr("Core mod"));
    addons = new QTreeWidgetItem(ui->tree_list);
    addons->setText(0, tr("Addons"));
    add_blue_marble = new QTreeWidgetItem(addons);
    add_blue_marble->setText(0, "Blue marble");
    add_mega_civ_pack = new QTreeWidgetItem(addons);
    add_mega_civ_pack->setText(0, tr("Mega civ pack"));
    add_more_music = new QTreeWidgetItem(addons);
    add_more_music->setText(0, tr("More music"));
    add_more_handicaps = new QTreeWidgetItem(addons);
    add_more_handicaps->setText(0, tr("More handicaps"));
    add_dinosaurs = new QTreeWidgetItem(addons);
    add_dinosaurs->setText(0, tr("Dinosaurs !"));
}

modules::~modules()
{
    delete ui;
}

void modules::on_tree_list_itemClicked(QTreeWidgetItem *item)
{
    if(core->isSelected())
    {
        ui->bt_remove->hide();
        ui->label->setText(QString("<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">%1</span></p></body></html>").arg(tr("Changes:")));
        ui->label_core_version->setText(QString("Version:\n%1").arg(svnLocalInfo()));
        ui->changelog_box->setText(svnGetChangelog(10));
        if(readCheckerParam("Main/LocalRev").toInt() < readCheckerParam("Update/DistantRev").toInt())
        {
            ui->bt_update->setText(tr("Update:") + "\n" + readCheckerParam("Main/DistantRev"));
            ui->bt_update->show();
        }
    }
    if(add_blue_marble->isSelected())
    {
        QString description = "BM Description";
        moduleInterface(check_addon_mcp(),description);
    }
    if(add_mega_civ_pack->isSelected())
    {
        QString description = "MCP Description";
        moduleInterface(check_addon_mcp(),description);
    }
    if(add_more_music->isSelected())
    {
        QString description = "MM Description";
        moduleInterface(check_addon_mcp(),description);
    }
    if(add_more_handicaps->isSelected())
    {
        QString description = "MH Description";
        moduleInterface(check_addon_mcp(),description);
    }
    if(add_dinosaurs->isSelected())
    {
        QString description = "Dino Description";
        moduleInterface(check_addon_mcp(),description);
    }
}

void modules::moduleInterface(QString version, QString description)
{
    ui->bt_remove->hide();
    ui->bt_update->hide();
    ui->label->setText(QString("<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">%1</span></p></body></html>").arg(tr("Description:")));
    ui->label_core_version->setText(tr("Installed:")+ "\n" + version);
    ui->changelog_box->setText(description);
    if(version == "Not installed")
    {
        ui->bt_remove->show();
        ui->bt_remove->setText("Install module");
    }
    else
    {
        ui->bt_remove->show();
        ui->bt_remove->setText("Remove module");
    }
}
