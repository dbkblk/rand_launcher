#include "optionbox.h"
#include "mainwindow.h"
#include "ui_optionbox.h"
#include "civ_functions.h"
#include "updatemanager.h"
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

    connect(chglog,SIGNAL(finished()),chglog->bt_chglog_close,SLOT(show()));

    // Link the svn signal to the main window labels

    connect(chglog,SIGNAL(finished()),parent,SLOT(UpdateWindowInfos()));

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
    qDebug() << "Check reading : " << readCheckerParam("MAIN/ExecutablePath");
    if(readCheckerParam("MAIN/ExecutablePath") == "error")
    {
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
    chglog->bt_chglog_close->hide();
    chglog->show();
    chglog->updateMode();
    bool value = false;
    chglog->execute("checker/svn.exe update",value);
    clearCache();

    msg_show = true;
    chglog->message = "The mod has been updated.";
}

void optionBox::on_opt_bt_cleanup_clicked()
{
    bool value = false;
    chglog->execute("checker/svn.exe cleanup",value);
    clearCache();
    QMessageBox::information(chglog, "Mod cleaned up", "The mod has been cleaned up. You can update the game now (it can grab the missing files).");
}

void optionBox::on_opt_bt_restore_clicked()
{
    chglog->bt_chglog_close->hide();
    chglog->show();
    chglog->updateMode();
    chglog->setWindowTitle("Reverting version...");
    bool value = false;
    chglog->execute("checker/svn.exe update -r PREV --accept theirs-full",value);
    clearCache();

    msg_show = true;
    chglog->message = "The mod has been reverted to the previous version.";
}

void optionBox::on_opt_bt_chooserev_clicked()
{
    QString dial_rev = QInputDialog::getText(this, "Revision selector", "Please enter the revision you want to revert to :", QLineEdit::Normal);
    qDebug() << dial_rev;
    QString cmd = "checker/svn.exe update -r " + dial_rev + " --accept theirs-full";
    bool value = false;
    chglog->bt_chglog_close->hide();
    chglog->show();
    chglog->updateMode();
    chglog->setWindowTitle("Reverting version...");
    chglog->execute(cmd,value);
    clearCache();

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
     if(readCheckerParam("MAIN/CheckerVersion") < readCheckerParam("MAIN/DistantCheckerVersion"))
     {
         QMessageBox upd_box;
         upd_box.setWindowTitle("Launcher update available");
         upd_box.setText("An update of the launcher is available.");
         upd_box.setInformativeText("Do you want to update ?");
         upd_box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
         int ret = upd_box.exec();
         switch (ret) {
             case QMessageBox::Ok :
                 launcherUpdate();
                 break;

             case QMessageBox::Cancel :
                 break;
         }

     }
     else
     {
         QMessageBox::information(0, "Information", "No update is available !");
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


void optionBox::on_opt_checkbox_formations_toggled(bool checked)
{
    if(checked)
    {
        setOptionFormations(true);
    }
    else
    {
        setOptionFormations(false);
    }
}

void optionBox::on_opt_checkbox_autoupdate_toggled(bool checked)
{
    if(checked)
    {
        setCheckerParam("MAIN/CheckerAutoUpdate","1");
    }
    else
    {
        setCheckerParam("MAIN/CheckerAutoUpdate","0");
    }

}
