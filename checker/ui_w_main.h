/********************************************************************************
** Form generated from reading UI file 'w_main.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_MAIN_H
#define UI_W_MAIN_H

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

class Ui_w_main
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
    QAction *actionClean_up;
    QAction *actionRevert_to_an_older_revision;
    QAction *actionAddon_Blue_marble;
    QAction *actionClear_cache;
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
    QMenu *menuMenu;
    QMenu *menuFix_installation;
    QMenu *menuCommunity;
    QMenu *menuTools;
    QMenu *menuDevelopment_tools;
    QMenu *menuLanguage;

    void setupUi(QMainWindow *w_main)
    {
        if (w_main->objectName().isEmpty())
            w_main->setObjectName(QStringLiteral("w_main"));
        w_main->setWindowModality(Qt::WindowModal);
        w_main->resize(600, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(w_main->sizePolicy().hasHeightForWidth());
        w_main->setSizePolicy(sizePolicy);
        w_main->setMinimumSize(QSize(600, 300));
        w_main->setMaximumSize(QSize(600, 300));
        w_main->setFocusPolicy(Qt::StrongFocus);
        w_main->setWindowTitle(QStringLiteral("MainWindow"));
        w_main->setStyleSheet(QStringLiteral(""));
        w_main->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        w_main->setAnimated(false);
        w_main->setUnifiedTitleAndToolBarOnMac(true);
        actionExit = new QAction(w_main);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setMenuRole(QAction::QuitRole);
        actionForum = new QAction(w_main);
        actionForum->setObjectName(QStringLiteral("actionForum"));
        actionAddon_Mega_Civ_Pack = new QAction(w_main);
        actionAddon_Mega_Civ_Pack->setObjectName(QStringLiteral("actionAddon_Mega_Civ_Pack"));
        actionBugreport = new QAction(w_main);
        actionBugreport->setObjectName(QStringLiteral("actionBugreport"));
        actionAbout_AND_Resurrection_team_forum = new QAction(w_main);
        actionAbout_AND_Resurrection_team_forum->setObjectName(QStringLiteral("actionAbout_AND_Resurrection_team_forum"));
        actionAddon_More_music_forum = new QAction(w_main);
        actionAddon_More_music_forum->setObjectName(QStringLiteral("actionAddon_More_music_forum"));
        actionOpen_mod_folder = new QAction(w_main);
        actionOpen_mod_folder->setObjectName(QStringLiteral("actionOpen_mod_folder"));
        actionGit_Pack_binaries = new QAction(w_main);
        actionGit_Pack_binaries->setObjectName(QStringLiteral("actionGit_Pack_binaries"));
        actionGit_Create_update_binary_pack = new QAction(w_main);
        actionGit_Create_update_binary_pack->setObjectName(QStringLiteral("actionGit_Create_update_binary_pack"));
        actionHelp_translate_the_mod = new QAction(w_main);
        actionHelp_translate_the_mod->setObjectName(QStringLiteral("actionHelp_translate_the_mod"));
        actionTranslate_the_mod_help = new QAction(w_main);
        actionTranslate_the_mod_help->setObjectName(QStringLiteral("actionTranslate_the_mod_help"));
        actionTranslate_the_launcher = new QAction(w_main);
        actionTranslate_the_launcher->setObjectName(QStringLiteral("actionTranslate_the_launcher"));
        languageEnglish = new QAction(w_main);
        languageEnglish->setObjectName(QStringLiteral("languageEnglish"));
        languageFrench = new QAction(w_main);
        languageFrench->setObjectName(QStringLiteral("languageFrench"));
        languageSinhala = new QAction(w_main);
        languageSinhala->setObjectName(QStringLiteral("languageSinhala"));
        languageHungarian = new QAction(w_main);
        languageHungarian->setObjectName(QStringLiteral("languageHungarian"));
        languageFinnish = new QAction(w_main);
        languageFinnish->setObjectName(QStringLiteral("languageFinnish"));
        languagePolish = new QAction(w_main);
        languagePolish->setObjectName(QStringLiteral("languagePolish"));
        languageItalian = new QAction(w_main);
        languageItalian->setObjectName(QStringLiteral("languageItalian"));
        languageSpanish = new QAction(w_main);
        languageSpanish->setObjectName(QStringLiteral("languageSpanish"));
        languageGerman = new QAction(w_main);
        languageGerman->setObjectName(QStringLiteral("languageGerman"));
        languageRussian = new QAction(w_main);
        languageRussian->setObjectName(QStringLiteral("languageRussian"));
        actionClean_up = new QAction(w_main);
        actionClean_up->setObjectName(QStringLiteral("actionClean_up"));
        actionRevert_to_an_older_revision = new QAction(w_main);
        actionRevert_to_an_older_revision->setObjectName(QStringLiteral("actionRevert_to_an_older_revision"));
        actionAddon_Blue_marble = new QAction(w_main);
        actionAddon_Blue_marble->setObjectName(QStringLiteral("actionAddon_Blue_marble"));
        actionClear_cache = new QAction(w_main);
        actionClear_cache->setObjectName(QStringLiteral("actionClear_cache"));
        centralWidget = new QWidget(w_main);
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

        w_main->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(w_main);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        menuMenu->setEnabled(true);
        menuMenu->setContextMenuPolicy(Qt::ActionsContextMenu);
        menuFix_installation = new QMenu(menuMenu);
        menuFix_installation->setObjectName(QStringLiteral("menuFix_installation"));
        menuCommunity = new QMenu(menuBar);
        menuCommunity->setObjectName(QStringLiteral("menuCommunity"));
        menuCommunity->setEnabled(true);
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuDevelopment_tools = new QMenu(menuTools);
        menuDevelopment_tools->setObjectName(QStringLiteral("menuDevelopment_tools"));
        menuDevelopment_tools->setEnabled(false);
        menuLanguage = new QMenu(menuBar);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        w_main->setMenuBar(menuBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuLanguage->menuAction());
        menuBar->addAction(menuCommunity->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuMenu->addAction(actionOpen_mod_folder);
        menuMenu->addAction(menuFix_installation->menuAction());
        menuMenu->addAction(actionExit);
        menuFix_installation->addAction(actionClear_cache);
        menuFix_installation->addAction(actionClean_up);
        menuFix_installation->addAction(actionRevert_to_an_older_revision);
        menuCommunity->addAction(actionForum);
        menuCommunity->addAction(actionBugreport);
        menuCommunity->addAction(actionAddon_Blue_marble);
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

        retranslateUi(w_main);

        QMetaObject::connectSlotsByName(w_main);
    } // setupUi

    void retranslateUi(QMainWindow *w_main)
    {
        actionExit->setText(QApplication::translate("w_main", "Exit", 0));
        actionForum->setText(QApplication::translate("w_main", "Forum", 0));
        actionAddon_Mega_Civ_Pack->setText(QApplication::translate("w_main", "Addon \"Mega Civ Pack\" (forum)", 0));
        actionBugreport->setText(QApplication::translate("w_main", "Bugreport (forum)", 0));
        actionAbout_AND_Resurrection_team_forum->setText(QApplication::translate("w_main", "About AND Resurrection team (forum)", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout_AND_Resurrection_team_forum->setToolTip(QApplication::translate("w_main", "About AND Resurrection team (forum)", 0));
#endif // QT_NO_TOOLTIP
        actionAddon_More_music_forum->setText(QApplication::translate("w_main", "Addon \"More music / More handicaps / Dinosaurs\" (forum)", 0));
        actionOpen_mod_folder->setText(QApplication::translate("w_main", "Open mod folder", 0));
        actionGit_Pack_binaries->setText(QApplication::translate("w_main", "Git: Create binary pack", 0));
        actionGit_Create_update_binary_pack->setText(QApplication::translate("w_main", "Git: Create update binary pack", 0));
        actionHelp_translate_the_mod->setText(QApplication::translate("w_main", "Translate the mod", 0));
        actionTranslate_the_mod_help->setText(QApplication::translate("w_main", "Help for translation (forum)", 0));
        actionTranslate_the_launcher->setText(QApplication::translate("w_main", "Translate the launcher", 0));
        languageEnglish->setText(QApplication::translate("w_main", "English", 0));
        languageFrench->setText(QApplication::translate("w_main", "French", 0));
        languageSinhala->setText(QApplication::translate("w_main", "Sinhala", 0));
        languageHungarian->setText(QApplication::translate("w_main", "Hungarian", 0));
        languageFinnish->setText(QApplication::translate("w_main", "Finnish", 0));
        languagePolish->setText(QApplication::translate("w_main", "Polish", 0));
        languageItalian->setText(QApplication::translate("w_main", "Italian", 0));
        languageSpanish->setText(QApplication::translate("w_main", "Spanish", 0));
        languageGerman->setText(QApplication::translate("w_main", "German", 0));
        languageRussian->setText(QApplication::translate("w_main", "Russian", 0));
        actionClean_up->setText(QApplication::translate("w_main", "Restore default state", 0));
        actionRevert_to_an_older_revision->setText(QApplication::translate("w_main", "Revert to an older revision...", 0));
        actionAddon_Blue_marble->setText(QApplication::translate("w_main", "Addon \"Blue marble\"", 0));
        actionClear_cache->setText(QApplication::translate("w_main", "Clear cache", 0));
        bt_launch->setText(QApplication::translate("w_main", "Launch Civilization IV", 0));
        bt_components->setText(QApplication::translate("w_main", "Manage modules", 0));
        bt_option->setText(QApplication::translate("w_main", "Options", 0));
        menuMenu->setTitle(QApplication::translate("w_main", "Menu", 0));
        menuFix_installation->setTitle(QApplication::translate("w_main", "Fix installation", 0));
        menuCommunity->setTitle(QApplication::translate("w_main", "Community", 0));
        menuTools->setTitle(QApplication::translate("w_main", "Help us to improve the mod !", 0));
        menuDevelopment_tools->setTitle(QApplication::translate("w_main", "Development tools", 0));
        menuLanguage->setTitle(QApplication::translate("w_main", "Language", 0));
        Q_UNUSED(w_main);
    } // retranslateUi

};

namespace Ui {
    class w_main: public Ui_w_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_MAIN_H
