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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QAction *actionAddon_More_music_forum;
    QAction *actionOpen_mod_folder;
    QAction *actionGit_Pack_binaries;
    QAction *actionGit_Create_update_binary_pack;
    QAction *actionHelp_translate_the_mod;
    QAction *actionTranslate_the_mod_help;
    QAction *actionTranslate_the_launcher;
    QAction *languageEnglish;
    QAction *languageFrench;
    QAction *languageSinhala;
    QAction *languageHungarian;
    QAction *languageFinnish;
    QAction *languagePolish;
    QAction *languageItalian;
    QAction *languageSpanish;
    QAction *languageGerman;
    QAction *languageRussian;
    QWidget *centralWidget;
    QLabel *lb_versions;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *bt_launch;
    QPushButton *bt_components;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *bt_option;
    QMenuBar *menuBar;
    QMenu *menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher;
    QMenu *menuCommunity;
    QMenu *menuTools;
    QMenu *menuDevelopment_tools;
    QMenu *menuLanguage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(600, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 300));
        MainWindow->setMaximumSize(QSize(600, 300));
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        MainWindow->setWindowTitle(QStringLiteral("MainWindow"));
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
        actionGit_Pack_binaries = new QAction(MainWindow);
        actionGit_Pack_binaries->setObjectName(QStringLiteral("actionGit_Pack_binaries"));
        actionGit_Create_update_binary_pack = new QAction(MainWindow);
        actionGit_Create_update_binary_pack->setObjectName(QStringLiteral("actionGit_Create_update_binary_pack"));
        actionHelp_translate_the_mod = new QAction(MainWindow);
        actionHelp_translate_the_mod->setObjectName(QStringLiteral("actionHelp_translate_the_mod"));
        actionTranslate_the_mod_help = new QAction(MainWindow);
        actionTranslate_the_mod_help->setObjectName(QStringLiteral("actionTranslate_the_mod_help"));
        actionTranslate_the_launcher = new QAction(MainWindow);
        actionTranslate_the_launcher->setObjectName(QStringLiteral("actionTranslate_the_launcher"));
        languageEnglish = new QAction(MainWindow);
        languageEnglish->setObjectName(QStringLiteral("languageEnglish"));
        languageFrench = new QAction(MainWindow);
        languageFrench->setObjectName(QStringLiteral("languageFrench"));
        languageSinhala = new QAction(MainWindow);
        languageSinhala->setObjectName(QStringLiteral("languageSinhala"));
        languageHungarian = new QAction(MainWindow);
        languageHungarian->setObjectName(QStringLiteral("languageHungarian"));
        languageFinnish = new QAction(MainWindow);
        languageFinnish->setObjectName(QStringLiteral("languageFinnish"));
        languagePolish = new QAction(MainWindow);
        languagePolish->setObjectName(QStringLiteral("languagePolish"));
        languageItalian = new QAction(MainWindow);
        languageItalian->setObjectName(QStringLiteral("languageItalian"));
        languageSpanish = new QAction(MainWindow);
        languageSpanish->setObjectName(QStringLiteral("languageSpanish"));
        languageGerman = new QAction(MainWindow);
        languageGerman->setObjectName(QStringLiteral("languageGerman"));
        languageRussian = new QAction(MainWindow);
        languageRussian->setObjectName(QStringLiteral("languageRussian"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        lb_versions = new QLabel(centralWidget);
        lb_versions->setObjectName(QStringLiteral("lb_versions"));
        lb_versions->setGeometry(QRect(480, 0, 111, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lb_versions->sizePolicy().hasHeightForWidth());
        lb_versions->setSizePolicy(sizePolicy1);
        lb_versions->setStyleSheet(QStringLiteral(""));
        lb_versions->setText(QStringLiteral("<html><head/><body><p><span style=\" color:#000000;\">TextLabel</span></p></body></html>"));
        lb_versions->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 160, 561, 101));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        bt_launch = new QPushButton(horizontalLayoutWidget);
        bt_launch->setObjectName(QStringLiteral("bt_launch"));
        sizePolicy.setHeightForWidth(bt_launch->sizePolicy().hasHeightForWidth());
        bt_launch->setSizePolicy(sizePolicy);
        bt_launch->setMinimumSize(QSize(175, 25));
        bt_launch->setAutoFillBackground(false);
        bt_launch->setStyleSheet(QStringLiteral("background-image: none"));
        bt_launch->setAutoDefault(false);
        bt_launch->setFlat(false);

        verticalLayout->addWidget(bt_launch);

        bt_components = new QPushButton(horizontalLayoutWidget);
        bt_components->setObjectName(QStringLiteral("bt_components"));
        bt_components->setMinimumSize(QSize(175, 25));

        verticalLayout->addWidget(bt_components);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        bt_option = new QPushButton(horizontalLayoutWidget);
        bt_option->setObjectName(QStringLiteral("bt_option"));
        bt_option->setMinimumSize(QSize(175, 25));
        bt_option->setStyleSheet(QStringLiteral("border-image: none"));
        bt_option->setFlat(false);

        verticalLayout_2->addWidget(bt_option);


        horizontalLayout->addLayout(verticalLayout_2);

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
        menuDevelopment_tools = new QMenu(menuTools);
        menuDevelopment_tools->setObjectName(QStringLiteral("menuDevelopment_tools"));
        menuDevelopment_tools->setEnabled(false);
        menuLanguage = new QMenu(menuBar);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->menuAction());
        menuBar->addAction(menuLanguage->menuAction());
        menuBar->addAction(menuCommunity->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->addAction(actionOpen_mod_folder);
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->addAction(actionExit);
        menuCommunity->addAction(actionForum);
        menuCommunity->addAction(actionBugreport);
        menuCommunity->addAction(actionAddon_Mega_Civ_Pack);
        menuCommunity->addAction(actionAddon_More_music_forum);
        menuCommunity->addAction(actionAbout_AND_Resurrection_team_forum);
        menuTools->addAction(actionHelp_translate_the_mod);
        menuTools->addAction(actionTranslate_the_launcher);
        menuTools->addAction(actionTranslate_the_mod_help);
        menuTools->addAction(menuDevelopment_tools->menuAction());
        menuDevelopment_tools->addAction(actionGit_Pack_binaries);
        menuDevelopment_tools->addAction(actionGit_Create_update_binary_pack);
        menuLanguage->addAction(languageEnglish);
        menuLanguage->addAction(languageFinnish);
        menuLanguage->addAction(languageFrench);
        menuLanguage->addAction(languageGerman);
        menuLanguage->addAction(languageHungarian);
        menuLanguage->addAction(languageItalian);
        menuLanguage->addAction(languagePolish);
        menuLanguage->addAction(languageRussian);
        menuLanguage->addAction(languageSinhala);
        menuLanguage->addAction(languageSpanish);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
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
        actionGit_Pack_binaries->setText(QApplication::translate("MainWindow", "Git: Create binary pack", 0));
        actionGit_Create_update_binary_pack->setText(QApplication::translate("MainWindow", "Git: Create update binary pack", 0));
        actionHelp_translate_the_mod->setText(QApplication::translate("MainWindow", "Translate the mod", 0));
        actionTranslate_the_mod_help->setText(QApplication::translate("MainWindow", "Help for translation (forum)", 0));
        actionTranslate_the_launcher->setText(QApplication::translate("MainWindow", "Translate the launcher", 0));
        languageEnglish->setText(QApplication::translate("MainWindow", "English", 0));
        languageFrench->setText(QApplication::translate("MainWindow", "French", 0));
        languageSinhala->setText(QApplication::translate("MainWindow", "Sinhala", 0));
        languageHungarian->setText(QApplication::translate("MainWindow", "Hungarian", 0));
        languageFinnish->setText(QApplication::translate("MainWindow", "Finnish", 0));
        languagePolish->setText(QApplication::translate("MainWindow", "Polish", 0));
        languageItalian->setText(QApplication::translate("MainWindow", "Italian", 0));
        languageSpanish->setText(QApplication::translate("MainWindow", "Spanish", 0));
        languageGerman->setText(QApplication::translate("MainWindow", "German", 0));
        languageRussian->setText(QApplication::translate("MainWindow", "Russian", 0));
        bt_launch->setText(QApplication::translate("MainWindow", "Launch Civilization IV", 0));
        bt_components->setText(QApplication::translate("MainWindow", "Manage modules", 0));
        bt_option->setText(QApplication::translate("MainWindow", "Options", 0));
        menuCivilization_4_Rise_of_Mankind_A_New_Dawn_2_Launcher->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuCommunity->setTitle(QApplication::translate("MainWindow", "Community", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Help us to improve the mod !", 0));
        menuDevelopment_tools->setTitle(QApplication::translate("MainWindow", "Development tools", 0));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
