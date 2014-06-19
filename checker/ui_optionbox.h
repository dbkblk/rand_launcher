/********************************************************************************
** Form generated from reading UI file 'optionbox.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONBOX_H
#define UI_OPTIONBOX_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optionBox
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *lb_modconf;
    QCheckBox *opt_checkbox_formations;
    QCheckBox *opt_checkbox_bluemarble;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_intcolor;
    QComboBox *colorBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *opt_bt_path;
    QLineEdit *opt_text_path;
    QSpacerItem *verticalSpacer;
    QLabel *lb_modconf_2;
    QCheckBox *checkerBox;
    QCheckBox *startBox;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *opt_checkbox_autoupdate;
    QPushButton *opt_bt_chklauncher;

    void setupUi(QWidget *optionBox)
    {
        if (optionBox->objectName().isEmpty())
            optionBox->setObjectName(QStringLiteral("optionBox"));
        optionBox->setWindowModality(Qt::WindowModal);
        optionBox->resize(450, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(optionBox->sizePolicy().hasHeightForWidth());
        optionBox->setSizePolicy(sizePolicy);
        optionBox->setMinimumSize(QSize(450, 300));
        optionBox->setMaximumSize(QSize(450, 300));
        optionBox->setFocusPolicy(Qt::StrongFocus);
        optionBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayoutWidget = new QWidget(optionBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 13, 431, 278));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(10, 0, 10, 0);
        lb_modconf = new QLabel(verticalLayoutWidget);
        lb_modconf->setObjectName(QStringLiteral("lb_modconf"));

        verticalLayout_4->addWidget(lb_modconf);

        opt_checkbox_formations = new QCheckBox(verticalLayoutWidget);
        opt_checkbox_formations->setObjectName(QStringLiteral("opt_checkbox_formations"));

        verticalLayout_4->addWidget(opt_checkbox_formations);

        opt_checkbox_bluemarble = new QCheckBox(verticalLayoutWidget);
        opt_checkbox_bluemarble->setObjectName(QStringLiteral("opt_checkbox_bluemarble"));

        verticalLayout_4->addWidget(opt_checkbox_bluemarble);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lb_intcolor = new QLabel(verticalLayoutWidget);
        lb_intcolor->setObjectName(QStringLiteral("lb_intcolor"));

        horizontalLayout->addWidget(lb_intcolor);

        colorBox = new QComboBox(verticalLayoutWidget);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorBox->sizePolicy().hasHeightForWidth());
        colorBox->setSizePolicy(sizePolicy1);
        colorBox->setMinimumSize(QSize(175, 25));

        horizontalLayout->addWidget(colorBox);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        opt_bt_path = new QPushButton(verticalLayoutWidget);
        opt_bt_path->setObjectName(QStringLiteral("opt_bt_path"));
        sizePolicy1.setHeightForWidth(opt_bt_path->sizePolicy().hasHeightForWidth());
        opt_bt_path->setSizePolicy(sizePolicy1);
        opt_bt_path->setMinimumSize(QSize(175, 25));
        opt_bt_path->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(opt_bt_path);


        verticalLayout_4->addLayout(horizontalLayout_2);

        opt_text_path = new QLineEdit(verticalLayoutWidget);
        opt_text_path->setObjectName(QStringLiteral("opt_text_path"));
        sizePolicy1.setHeightForWidth(opt_text_path->sizePolicy().hasHeightForWidth());
        opt_text_path->setSizePolicy(sizePolicy1);
        opt_text_path->setMinimumSize(QSize(224, 25));
        opt_text_path->setMaximumSize(QSize(475, 16777215));
        opt_text_path->setReadOnly(true);

        verticalLayout_4->addWidget(opt_text_path);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer);

        lb_modconf_2 = new QLabel(verticalLayoutWidget);
        lb_modconf_2->setObjectName(QStringLiteral("lb_modconf_2"));

        verticalLayout_4->addWidget(lb_modconf_2);

        checkerBox = new QCheckBox(verticalLayoutWidget);
        checkerBox->setObjectName(QStringLiteral("checkerBox"));

        verticalLayout_4->addWidget(checkerBox);

        startBox = new QCheckBox(verticalLayoutWidget);
        startBox->setObjectName(QStringLiteral("startBox"));

        verticalLayout_4->addWidget(startBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        opt_checkbox_autoupdate = new QCheckBox(verticalLayoutWidget);
        opt_checkbox_autoupdate->setObjectName(QStringLiteral("opt_checkbox_autoupdate"));

        horizontalLayout_3->addWidget(opt_checkbox_autoupdate);

        opt_bt_chklauncher = new QPushButton(verticalLayoutWidget);
        opt_bt_chklauncher->setObjectName(QStringLiteral("opt_bt_chklauncher"));
        sizePolicy1.setHeightForWidth(opt_bt_chklauncher->sizePolicy().hasHeightForWidth());
        opt_bt_chklauncher->setSizePolicy(sizePolicy1);
        opt_bt_chklauncher->setMinimumSize(QSize(175, 25));
        opt_bt_chklauncher->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_3->addWidget(opt_bt_chklauncher);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(optionBox);

        QMetaObject::connectSlotsByName(optionBox);
    } // setupUi

    void retranslateUi(QWidget *optionBox)
    {
        optionBox->setWindowTitle(QApplication::translate("optionBox", "Options", 0));
        lb_modconf->setText(QApplication::translate("optionBox", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Mod configuration :</span></p></body></html>", 0));
        opt_checkbox_formations->setText(QApplication::translate("optionBox", "Enable formations (more graphical units)", 0));
        opt_checkbox_bluemarble->setText(QApplication::translate("optionBox", "Enable Blue Marble (alternative terrain graphics)", 0));
        lb_intcolor->setText(QApplication::translate("optionBox", "Interface color :", 0));
        colorBox->clear();
        colorBox->insertItems(0, QStringList()
         << QApplication::translate("optionBox", "Black", 0)
         << QApplication::translate("optionBox", "Coal", 0)
         << QApplication::translate("optionBox", "Dark red", 0)
         << QApplication::translate("optionBox", "Forest", 0)
         << QApplication::translate("optionBox", "Purple", 0)
         << QApplication::translate("optionBox", "Red", 0)
         << QApplication::translate("optionBox", "Silver", 0)
         << QApplication::translate("optionBox", "Cerulean", 0)
        );
        label->setText(QApplication::translate("optionBox", "Game path :", 0));
        opt_bt_path->setText(QApplication::translate("optionBox", "Select game path", 0));
        lb_modconf_2->setText(QApplication::translate("optionBox", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Launcher configuration :</span></p></body></html>", 0));
        checkerBox->setText(QApplication::translate("optionBox", "Close the launcher when game start", 0));
        startBox->setText(QApplication::translate("optionBox", "Autostart the mod with the game", 0));
        opt_checkbox_autoupdate->setText(QApplication::translate("optionBox", "Automatically update the launcher", 0));
        opt_bt_chklauncher->setText(QApplication::translate("optionBox", "Check for launcher update", 0));
    } // retranslateUi

};

namespace Ui {
    class optionBox: public Ui_optionBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONBOX_H
