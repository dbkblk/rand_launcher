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

    // Set labels
    ui->bt_update->hide();
    ui->label->setText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">" + QString(tr("Changes (last 50) :")) + "</span></p></body></html>");
}

w_modules::~w_modules()
{
    delete ui;
}

void w_modules::on_bt_update_clicked()
{
    f_check *launch = new f_check;
    connect(launch, SIGNAL(exit()), this, SLOT(terminate()));
    launch->PrepareUpdate();
    launch->ActionUpdate();
}

void w_modules::terminate(){
    emit exit();
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
