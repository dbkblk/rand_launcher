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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
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
    QWidget *centralWidget;
    QLabel *label;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPushButton *cleanupButton;
    QPushButton *updateButton;
    QPushButton *revertButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *colorBox;
    QLabel *label_5;
    QPushButton *autostartButton;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QMenu *menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher;
    QMenu *menuCommunity;
    QStatusBar *statusBar;

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
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 20, 601, 21));
        label->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 100, 161, 151));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(label_2);

        cleanupButton = new QPushButton(verticalLayoutWidget_2);
        cleanupButton->setObjectName(QStringLiteral("cleanupButton"));

        verticalLayout_2->addWidget(cleanupButton);

        updateButton = new QPushButton(verticalLayoutWidget_2);
        updateButton->setObjectName(QStringLiteral("updateButton"));

        verticalLayout_2->addWidget(updateButton);

        revertButton = new QPushButton(verticalLayoutWidget_2);
        revertButton->setObjectName(QStringLiteral("revertButton"));

        verticalLayout_2->addWidget(revertButton);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(190, 100, 149, 149));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        colorBox = new QComboBox(widget);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        colorBox->setEditable(false);

        verticalLayout->addWidget(colorBox);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        autostartButton = new QPushButton(widget);
        autostartButton->setObjectName(QStringLiteral("autostartButton"));

        verticalLayout->addWidget(autostartButton);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher = new QMenu(menuBar);
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setObjectName(QStringLiteral("menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher"));
        menuCommunity = new QMenu(menuBar);
        menuCommunity->setObjectName(QStringLiteral("menuCommunity"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->menuAction());
        menuBar->addAction(menuCommunity->menuAction());
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->addAction(actionExit);
        menuCommunity->addAction(actionForum);
        menuCommunity->addAction(actionBugreport);
        menuCommunity->addAction(actionAddon_Mega_Civ_Pack);
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
        label->setText(QApplication::translate("MainWindow", "Civilization 4 - Rise of Mankind : A New Dawn 2 - Launcher", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600;\">Update process</span></p></body></html>", 0));
        cleanupButton->setText(QApplication::translate("MainWindow", "Clean up the installation", 0));
        updateButton->setText(QApplication::translate("MainWindow", "Check for update", 0));
        revertButton->setText(QApplication::translate("MainWindow", "Revert to previous version", 0));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Mod configuration</span></p></body></html>", 0));
        label_4->setText(QApplication::translate("MainWindow", "Change interface color :", 0));
        colorBox->clear();
        colorBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Black", 0)
         << QApplication::translate("MainWindow", "Coal", 0)
         << QApplication::translate("MainWindow", "Dark Red", 0)
         << QApplication::translate("MainWindow", "Forest", 0)
         << QApplication::translate("MainWindow", "Purple", 0)
         << QApplication::translate("MainWindow", "Red", 0)
         << QApplication::translate("MainWindow", "Silver", 0)
         << QApplication::translate("MainWindow", "Cerulean", 0)
        );
        label_5->setText(QApplication::translate("MainWindow", "Change startup settings :", 0));
        autostartButton->setText(QApplication::translate("MainWindow", "Launch the mod by default", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Restore default config.", 0));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuCommunity->setTitle(QApplication::translate("MainWindow", "Community", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
