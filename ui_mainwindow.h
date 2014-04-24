/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
    QWidget *centralWidget;
    QLabel *lb_title;
    QPushButton *bt_launch;
    QPushButton *bt_update;
    QPushButton *bt_option;
    QLabel *lb_versions;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher;
    QMenu *menuCommunity;

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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        lb_title = new QLabel(centralWidget);
        lb_title->setObjectName(QStringLiteral("lb_title"));
        lb_title->setGeometry(QRect(0, 0, 601, 71));
        lb_title->setAlignment(Qt::AlignCenter);
        bt_launch = new QPushButton(centralWidget);
        bt_launch->setObjectName(QStringLiteral("bt_launch"));
        bt_launch->setGeometry(QRect(10, 230, 151, 23));
        bt_launch->setAutoFillBackground(false);
        bt_launch->setStyleSheet(QStringLiteral("background-image: none"));
        bt_launch->setAutoDefault(false);
        bt_launch->setFlat(false);
        bt_update = new QPushButton(centralWidget);
        bt_update->setObjectName(QStringLiteral("bt_update"));
        bt_update->setGeometry(QRect(170, 230, 136, 23));
        bt_option = new QPushButton(centralWidget);
        bt_option->setObjectName(QStringLiteral("bt_option"));
        bt_option->setGeometry(QRect(450, 230, 136, 23));
        bt_option->setStyleSheet(QStringLiteral("border-image: none"));
        bt_option->setFlat(false);
        lb_versions = new QLabel(centralWidget);
        lb_versions->setObjectName(QStringLiteral("lb_versions"));
        lb_versions->setGeometry(QRect(365, 249, 221, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lb_versions->sizePolicy().hasHeightForWidth());
        lb_versions->setSizePolicy(sizePolicy1);
        lb_versions->setStyleSheet(QStringLiteral(""));
        lb_versions->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(470, 180, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher = new QMenu(menuBar);
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setObjectName(QStringLiteral("menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher"));
        menuCommunity = new QMenu(menuBar);
        menuCommunity->setObjectName(QStringLiteral("menuCommunity"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->menuAction());
        menuBar->addAction(menuCommunity->menuAction());
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->addAction(actionExit);
        menuCommunity->addAction(actionForum);
        menuCommunity->addAction(actionBugreport);
        menuCommunity->addAction(actionAddon_Mega_Civ_Pack);
        menuCommunity->addAction(actionAddon_More_music_forum);
        menuCommunity->addAction(actionAbout_AND_Resurrection_team_forum);

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
        lb_title->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600; color:#ffffff;\">Civilization IV - A New Dawn 2</span></p></body></html>", 0));
        bt_launch->setText(QApplication::translate("MainWindow", "Launch Civilization IV", 0));
        bt_update->setText(QApplication::translate("MainWindow", "Check for update", 0));
        bt_option->setText(QApplication::translate("MainWindow", "Options", 0));
        lb_versions->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">TextLabel</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuCommunity->setTitle(QApplication::translate("MainWindow", "Community", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
