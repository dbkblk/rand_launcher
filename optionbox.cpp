#include "optionbox.h"
#include "ui_optionbox.h"
#include "civ_functions.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

optionBox::optionBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optionBox)
{
    ui->setupUi(this);

    // Set the detected color
    ui->colorBox->setCurrentIndex(readColorsCounter());
}

optionBox::~optionBox()
{
    delete ui;
}

// Buttons actions
/*
void MainWindow::on_autostartButton_clicked()
{
    setStartup();
    QMessageBox::information(this, "Information", "The mod has been set to autostart with the game.");
}

void MainWindow::on_pushButton_4_clicked()
{
    restoreBackup();
    QMessageBox::information(this, "Information", "The config file has been reverted to the previous configuration.");
}


void MainWindow::on_colorBox_currentIndexChanged(const QString &colorName)
{
    QString colorUI = colorName + " UI";
    setColors(colorUI.toStdString().c_str());
}*/


void optionBox::on_opt_bt_update_clicked()
{
    checkUpdate();
    QMessageBox::information(this, "Information", "The mod is up-to-date.");
}

void optionBox::on_opt_bt_cleanup_clicked()
{
    cleanUp();
    QMessageBox::information(this, "Information", "The mod has been cleaned up. You can update the game now (it can grab the missing files).");
}

void optionBox::on_opt_bt_restore_clicked()
{
    rollBack();
    QMessageBox::information(this, "Information", "The mod has been reverted to the previous version.");
}

void optionBox::on_opt_bt_chooserev_clicked()
{
    QString dial_rev = QInputDialog::getText(this, "Revision selector", "Please enter the revision you want to revert to :", QLineEdit::Normal);
    qDebug() << dial_rev;
    QString cmd = "checker/svn.exe update -r ";
    QString cmd_part2 = " --accept theirs-full && echo The cache will now be cleared && TIMEOUT 3";
    cmd += dial_rev + cmd_part2;
    qDebug() << cmd;
    system(cmd.toStdString().c_str());
    //system("checker\\svn.exe update -r PREV --accept theirs-full && echo The cache will now be cleared && TIMEOUT 3");
}
