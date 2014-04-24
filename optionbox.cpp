#include "optionbox.h"
#include "ui_optionbox.h"
#include "civ_functions.h"
#include "updatebox.h"
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>

optionBox::optionBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::optionBox)
{
    ui->setupUi(this);
    chglog = new updatebox(this);

    // Link the close update button to a bool message
    connect(chglog->bt_chglog_close,SIGNAL(clicked()),this,SLOT(chglog_msg_info()));

    // Set the detected color
    ui->colorBox->setCurrentIndex(readColorsCounter());

    // Set default startBox state
    if(readConfigParam("CONFIG/Mod") == "Mods/Rise of Mankind - A New Dawn") {
        ui->startBox->setChecked(1);
    }
    else {
        ui->startBox->setChecked(0);
    }
    // Set default checkerBox state
    if(readCheckerParam("MAIN/QuitLauncher") == "1") {
        ui->checkerBox->setChecked(1);
    }
    else {
        ui->checkerBox->setChecked(0);
    }
    // Set default opt_text_path
    if(readCheckerParam("MAIN/ExecutablePath") == NULL) {
        ui->opt_text_path->setText("No path specified");
    }
    else {
        ui->opt_text_path->setText(readCheckerParam("MAIN/ExecutablePath"));
    }
}

optionBox::~optionBox()
{
    delete ui;
}

// Buttons actions

void optionBox::on_opt_bt_update_clicked()
{
    chglog->show();
    chglog->updateMode();
    bool value = false;
    chglog->execute("checker/svn.exe update",value);
    clearCache();

    chglog->bt_chglog_close->show();
    msg_show = true;
    chglog->message = "The mod has been updated.";
}

void optionBox::on_opt_bt_cleanup_clicked()
{
    chglog->show();
    chglog->updateMode();
    chglog->setWindowTitle("Cleaning up...");
    bool value = false;
    chglog->execute("checker/svn.exe cleanup",value);
    clearCache();
    int msg_box = 0;

    chglog->bt_chglog_close->show();
    msg_show = true;
    chglog->message = "The mod has been cleaned up. You can update the game now (it can grab the missing files).";
}

void optionBox::on_opt_bt_restore_clicked()
{
    chglog->show();
    chglog->updateMode();
    chglog->setWindowTitle("Reverting version...");
    bool value = false;
    chglog->execute("checker/svn.exe update -r PREV --accept theirs-full",value);
    clearCache();

    chglog->bt_chglog_close->show();
    msg_show = true;
    chglog->message = "The mod has been reverted to the previous version.";
}

void optionBox::on_opt_bt_chooserev_clicked()
{
    QString dial_rev = QInputDialog::getText(this, "Revision selector", "Please enter the revision you want to revert to :", QLineEdit::Normal);
    qDebug() << dial_rev;
    QString cmd = "checker/svn.exe update -r " + dial_rev + " --accept theirs-full";
    bool value = false;
    chglog->show();
    chglog->updateMode();
    chglog->setWindowTitle("Reverting version...");
    chglog->execute(cmd,value);
    clearCache();

    chglog->bt_chglog_close->show();
    msg_show = true;
    chglog->message = "The mod has been reverted to the revision " + dial_rev;
}

void optionBox::on_colorBox_currentIndexChanged(const QString &colorName)
{
    QString colorUI = colorName + " UI";
    setColors(colorUI.toStdString().c_str());
}

void optionBox::on_startBox_toggled(bool checked)
{
    if(!checked) {
        setConfigParam("CONFIG/Mod", "0");
    }
    if(checked) {
        setConfigParam("CONFIG/Mod", "Mods/Rise of Mankind - A New Dawn");
    }
}

void optionBox::on_checkerBox_toggled(bool checked)
{
    if(checked) {
        setCheckerParam("MAIN/QuitLauncher", "1");
    }
    if(!checked) {
        setCheckerParam("MAIN/QuitLauncher", "0");
    }
}

void optionBox::on_opt_bt_path_clicked()
{
    QString exeloc = QFileDialog::getOpenFileName(0, "Find Civ. IV executable", QString(), "(Civ4BeyondSword.exe)");
    setCheckerParam("MAIN/ExecutablePath",exeloc);
    if(exeloc != NULL) {
        ui->opt_text_path->setText(exeloc);
        QMessageBox::information(0, "Information", "The game path has been changed");
        return;
    }
    if(exeloc == NULL) {
        ui->opt_text_path->setText("No game path specified.");
        return;
    }
}


void optionBox::on_opt_bt_chklauncher_clicked()
{
    switch(launcherCheck()){
        case 0 :
            QMessageBox::information(0, "Information", "No update is available !");
            break;

        case 1 :
            QMessageBox::information(0, "Information", "The update has been canceled.");
            break;

        case 2 :
            QMessageBox::information(0, "Information", "Can't contact the update server.");
            break;
    }
}

void optionBox::on_opt_bt_changelog_clicked()
{
    chglog->show();
    chglog->changelogMode();
    bool value = true;
    chglog->execute("checker/svn.exe log -l 10 ", value);
    msg_show = false;
}

void optionBox::chglog_msg_info()
{
    if(msg_show) {
        QMessageBox::information(this, "Information", chglog->message);
        chglog->close();
    }
    else {
        chglog->close();
    }

}

