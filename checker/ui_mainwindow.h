/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionForum;
    QAction *actionAddon_Mega_Civ_Pack;
    QAction *actionBugreport;
    QAction *actionAbout_AND_Resurrection_team_forum;
    QAction *actionAddon_More_music_forum;
    QAction *actionOpen_mod_folder;
    QAction *actionTest;
    QAction *actionTest_2;
    QWidget *centralWidget;
    QPushButton *bt_launch;
    QPushButton *bt_option;
    QLabel *lb_versions;
    QPushButton *bt_components;
    QMenuBar *menuBar;
    QMenu *menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher;
    QMenu *menuCommunity;
    QMenu *menuTools;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 300));
        MainWindow->setMaximumSize(QSize(600, 300));
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        MainWindow->setDocumentMode(false);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionForum = new QAction(MainWindow);
        actionForum->setObjectName(QStringLiteral("actionForum"));
        actionAddon_Mega_Civ_Pack = new QAction(MainWindow);
        actionAddon_Mega_Civ_Pack->setObjectName(QStringLiteral("actionAddon_Mega_Civ_Pack"));
        actionBugreport = new QAction(MainWindow);
        actionBugreport->setObjectName(QStringLiteral("actionBugreport"));
        actionAbout_AND_Resurrection_team_forum = new QAction(MainWindow);
        actionAbout_AND_Resurrection_team_forum->setObjectName(QStringLiteral("actionAbout_AND_Resurrection_team_forum"));
        actionAddon_More_music_forum = new QAction(MainWindow);
        actionAddon_More_music_forum->setObjectName(QStringLiteral("actionAddon_More_music_forum"));
        actionOpen_mod_folder = new QAction(MainWindow);
        actionOpen_mod_folder->setObjectName(QStringLiteral("actionOpen_mod_folder"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionTest_2 = new QAction(MainWindow);
        actionTest_2->setObjectName(QStringLiteral("actionTest_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        bt_launch = new QPushButton(centralWidget);
        bt_launch->setObjectName(QStringLiteral("bt_launch"));
        bt_launch->setGeometry(QRect(10, 230, 151, 23));
        bt_launch->setAutoFillBackground(false);
        bt_launch->setStyleSheet(QStringLiteral("background-image: none"));
        bt_launch->setAutoDefault(false);
        bt_launch->setFlat(false);
        bt_option = new QPushButton(centralWidget);
        bt_option->setObjectName(QStringLiteral("bt_option"));
        bt_option->setGeometry(QRect(450, 230, 131, 23));
        bt_option->setStyleSheet(QStringLiteral("border-image: none"));
        bt_option->setFlat(false);
        lb_versions = new QLabel(centralWidget);
        lb_versions->setObjectName(QStringLiteral("lb_versions"));
        lb_versions->setGeometry(QRect(480, 0, 111, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lb_versions->sizePolicy().hasHeightForWidth());
        lb_versions->setSizePolicy(sizePolicy1);
        lb_versions->setStyleSheet(QStringLiteral(""));
        lb_versions->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        bt_components = new QPushButton(centralWidget);
        bt_components->setObjectName(QStringLiteral("bt_components"));
        bt_components->setGeometry(QRect(170, 230, 131, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher = new QMenu(menuBar);
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setObjectName(QStringLiteral("menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher"));
        menuCommunity = new QMenu(menuBar);
        menuCommunity->setObjectName(QStringLiteral("menuCommunity"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->menuAction());
        menuBar->addAction(menuCommunity->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->addAction(actionExit);
        menuCommunity->addAction(actionForum);
        menuCommunity->addAction(actionBugreport);
        menuCommunity->addAction(actionAddon_Mega_Civ_Pack);
        menuCommunity->addAction(actionAddon_More_music_forum);
        menuCommunity->addAction(actionAbout_AND_Resurrection_team_forum);
        menuTools->addAction(actionOpen_mod_folder);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionForum->setText(QApplication::translate("MainWindow", "Forum", 0));
        actionAddon_Mega_Civ_Pack->setText(QApplication::translate("MainWindow", "Addon \"Mega Civ Pack\" (forum)", 0));
        actionBugreport->setText(QApplication::translate("MainWindow", "Bugreport (forum)", 0));
        actionAbout_AND_Resurrection_team_forum->setText(QApplication::translate("MainWindow", "About AND Resurrection team (forum)", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout_AND_Resurrection_team_forum->setToolTip(QApplication::translate("MainWindow", "About AND Resurrection team (forum)", 0));
#endif // QT_NO_TOOLTIP
        actionAddon_More_music_forum->setText(QApplication::translate("MainWindow", "Addon \"More music\" (forum)", 0));
        actionOpen_mod_folder->setText(QApplication::translate("MainWindow", "Open mod folder", 0));
        actionTest->setText(QApplication::translate("MainWindow", "test", 0));
        actionTest_2->setText(QApplication::translate("MainWindow", "test", 0));
        bt_launch->setText(QApplication::translate("MainWindow", "Launch Civilization IV", 0));
        bt_option->setText(QApplication::translate("MainWindow", "Options", 0));
        lb_versions->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">TextLabel</span></p></body></html>", 0));
        bt_components->setText(QApplication::translate("MainWindow", "Install / update modules", 0));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuCommunity->setTitle(QApplication::translate("MainWindow", "Community", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
