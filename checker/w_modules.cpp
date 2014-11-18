#include "w_modules.h"
#include "ui_w_modules.h"
#include "f_civ.h"
#include "f_check.h"

#include <QtCore>

w_modules::w_modules(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::w_modules)
{
    ui->setupUi(this);

    // Set version label
    ui->bt_update->hide();
}

w_modules::~w_modules()
{
    delete ui;
}

void w_modules::on_bt_update_clicked()
{
    f_check launch;
    launch.ActionUpdate();
}

void w_modules::UpdateWindow()
{
    QString result = "<p><span style=\" font-size:10pt; font-weight:600;\">" + tr("Local") + " :<br></span><span style=\" font-size:9pt; \">" + readCheckerParam("Main/LocalRev") +"</span></p>" + "<p><span style=\" font-size:10pt; font-weight:600;\">" + tr("Distant") + " :<br></span><span style=\" font-size:9pt; \">" + readCheckerParam("Update/DistantRev") +"</span></p>";
    ui->label_version->setText(result);

    // Check for update
    if(readCheckerParam("Main/LocalRev") < readCheckerParam("Update/DistantRev")) {
        qDebug() << "Update available !";
        ui->bt_update->show();
    }

    // Set changelog
    f_check changes;
    ui->changelog_box->setText(changes.ExtractChangelog("checker/changelog_last.xml"));

    // Retranslate
    ui->retranslateUi(this);
}
