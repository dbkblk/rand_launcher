#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_installBox.h"
#include <QtCore>
#include <QDesktopServices>
#include <QMessageBox>
#include <QDialog>
#include <QProcess>
#include <iostream>
#include <string>
#include <civ_functions.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setWindowTitle("Civilization IV: A New Dawn 2");

    // Setting the correct colorBox value
    ui->colorBox->setCurrentIndex(readColorsCounter());
}

MainWindow::~MainWindow()
{
    delete ui;
}

installBox::installBox(QDialog *parent) :
  QDialog(parent),
  ui(new Ui::installBox)
{
    ui->setupUi(this);
}

void MainWindow::on_pushButton_5_clicked()
{
    QDesktopServices::openUrl(QUrl("http://tortoisesvn.net/downloads.html"));
}

void MainWindow::on_actionForum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/forumdisplay.php?f=369"));
}

void MainWindow::on_actionAddon_Mega_Civ_Pack_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=521289"));
}

void MainWindow::on_actionBugreport_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=474185"));
}

void MainWindow::on_actionAbout_AND_Resurrection_team_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=471460"));
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

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

void MainWindow::on_updateButton_clicked()
{
    checkUpdate();
    QMessageBox::information(this, "Information", "The mod is up-to-date.");
}

void MainWindow::on_revertButton_clicked()
{
    rollBack();
    QMessageBox::information(this, "Information", "The mod has been reverted to the previous version.");
}

void MainWindow::on_cleanupButton_clicked()
{
    cleanUp();
    QMessageBox::information(this, "Information", "The mod has been cleaned up. You can update the game now (it can grab the missing files).");
}

void MainWindow::on_colorBox_currentIndexChanged(const QString &colorName)
{
    QString colorUI = colorName + " UI";
    setColors(colorUI.toStdString().c_str());
}

void installBox::on_buttonBox_accepted()
{
    installMod();
}

void installBox::on_buttonBox_rejected()
{
    qApp->exit();
}

void MainWindow::on_actionAddon_More_music_forum_triggered()
{
    QDesktopServices::openUrl(QUrl("http://forums.civfanatics.com/showthread.php?t=523763"));
}

void MainWindow::on_pushButton_clicked()
{
    //QString bt_exe = readXML("version.xml","exelocation");
    //qDebug() << bt_exe;
    QProcess *start_civ = new QProcess(0);
    start_civ->start("S:\Downloads\La motivation chez les réservistes.pdf");
}
