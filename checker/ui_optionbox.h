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
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *lb_modconf;
    QLabel *lb_intcolor;
    QComboBox *colorBox;
    QCheckBox *opt_checkbox_formations;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *opt_bt_path;
    QLineEdit *opt_text_path;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *lb_modconf_2;
    QCheckBox *checkerBox;
    QCheckBox *startBox;
    QCheckBox *opt_checkbox_autoupdate;
    QPushButton *opt_bt_chklauncher;

    void setupUi(QWidget *optionBox)
    {
        if (optionBox->objectName().isEmpty())
            optionBox->setObjectName(QStringLiteral("optionBox"));
        optionBox->setWindowModality(Qt::WindowModal);
        optionBox->resize(250, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(optionBox->sizePolicy().hasHeightForWidth());
        optionBox->setSizePolicy(sizePolicy);
        optionBox->setMinimumSize(QSize(250, 300));
        optionBox->setMaximumSize(QSize(250, 300));
        optionBox->setFocusPolicy(Qt::StrongFocus);
        optionBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayoutWidget = new QWidget(optionBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 231, 273));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lb_modconf = new QLabel(horizontalLayoutWidget);
        lb_modconf->setObjectName(QStringLiteral("lb_modconf"));

        verticalLayout_2->addWidget(lb_modconf);

        lb_intcolor = new QLabel(horizontalLayoutWidget);
        lb_intcolor->setObjectName(QStringLiteral("lb_intcolor"));

        verticalLayout_2->addWidget(lb_intcolor);

        colorBox = new QComboBox(horizontalLayoutWidget);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        colorBox->setMaximumSize(QSize(150, 16777215));
        colorBox->setEditable(false);

        verticalLayout_2->addWidget(colorBox);

        opt_checkbox_formations = new QCheckBox(horizontalLayoutWidget);
        opt_checkbox_formations->setObjectName(QStringLiteral("opt_checkbox_formations"));

        verticalLayout_2->addWidget(opt_checkbox_formations);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        opt_bt_path = new QPushButton(horizontalLayoutWidget);
        opt_bt_path->setObjectName(QStringLiteral("opt_bt_path"));
        opt_bt_path->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(opt_bt_path);


        verticalLayout_2->addLayout(horizontalLayout_2);

        opt_text_path = new QLineEdit(horizontalLayoutWidget);
        opt_text_path->setObjectName(QStringLiteral("opt_text_path"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(opt_text_path->sizePolicy().hasHeightForWidth());
        opt_text_path->setSizePolicy(sizePolicy1);
        opt_text_path->setMinimumSize(QSize(224, 0));
        opt_text_path->setMaximumSize(QSize(475, 16777215));
        opt_text_path->setReadOnly(true);

        verticalLayout_2->addWidget(opt_text_path);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        lb_modconf_2 = new QLabel(horizontalLayoutWidget);
        lb_modconf_2->setObjectName(QStringLiteral("lb_modconf_2"));

        verticalLayout_2->addWidget(lb_modconf_2);

        checkerBox = new QCheckBox(horizontalLayoutWidget);
        checkerBox->setObjectName(QStringLiteral("checkerBox"));

        verticalLayout_2->addWidget(checkerBox);

        startBox = new QCheckBox(horizontalLayoutWidget);
        startBox->setObjectName(QStringLiteral("startBox"));

        verticalLayout_2->addWidget(startBox);

        opt_checkbox_autoupdate = new QCheckBox(horizontalLayoutWidget);
        opt_checkbox_autoupdate->setObjectName(QStringLiteral("opt_checkbox_autoupdate"));

        verticalLayout_2->addWidget(opt_checkbox_autoupdate);

        opt_bt_chklauncher = new QPushButton(horizontalLayoutWidget);
        opt_bt_chklauncher->setObjectName(QStringLiteral("opt_bt_chklauncher"));
        opt_bt_chklauncher->setMaximumSize(QSize(150, 16777215));

        verticalLayout_2->addWidget(opt_bt_chklauncher);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(optionBox);

        QMetaObject::connectSlotsByName(optionBox);
    } // setupUi

    void retranslateUi(QWidget *optionBox)
    {
        optionBox->setWindowTitle(QApplication::translate("optionBox", "Options", 0));
        lb_modconf->setText(QApplication::translate("optionBox", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Mod configuration :</span></p></body></html>", 0));
        lb_intcolor->setText(QApplication::translate("optionBox", "Interface color :", 0));
        colorBox->clear();
        colorBox->insertItems(0, QStringList()
         << QApplication::translate("optionBox", "Black", 0)
         << QApplication::translate("optionBox", "Coal", 0)
         << QApplication::translate("optionBox", "Dark Red", 0)
         << QApplication::translate("optionBox", "Forest", 0)
         << QApplication::translate("optionBox", "Purple", 0)
         << QApplication::translate("optionBox", "Red", 0)
         << QApplication::translate("optionBox", "Silver", 0)
         << QApplication::translate("optionBox", "Cerulean", 0)
        );
        opt_checkbox_formations->setText(QApplication::translate("optionBox", "Enable formations (more graphical units)", 0));
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
