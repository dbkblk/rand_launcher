/********************************************************************************
** Form generated from reading UI file 'optionbox.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QPushButton *opt_bt_update;
    QPushButton *opt_bt_cleanup;
    QPushButton *opt_bt_restore;
    QPushButton *opt_bt_chooserev;
    QPushButton *opt_bt_chklauncher;
    QVBoxLayout *verticalLayout_2;
    QLabel *lb_modconf;
    QSpacerItem *verticalSpacer_2;
    QLabel *lb_intcolor;
    QComboBox *colorBox;
    QCheckBox *startBox;
    QCheckBox *checkerBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *opt_bt_path;
    QLineEdit *opt_text_path;

    void setupUi(QWidget *optionBox)
    {
        if (optionBox->objectName().isEmpty())
            optionBox->setObjectName(QStringLiteral("optionBox"));
        optionBox->resize(500, 250);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(optionBox->sizePolicy().hasHeightForWidth());
        optionBox->setSizePolicy(sizePolicy);
        optionBox->setFocusPolicy(Qt::StrongFocus);
        optionBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayoutWidget = new QWidget(optionBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 9, 461, 231));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        opt_bt_update = new QPushButton(horizontalLayoutWidget);
        opt_bt_update->setObjectName(QStringLiteral("opt_bt_update"));

        verticalLayout->addWidget(opt_bt_update);

        opt_bt_cleanup = new QPushButton(horizontalLayoutWidget);
        opt_bt_cleanup->setObjectName(QStringLiteral("opt_bt_cleanup"));

        verticalLayout->addWidget(opt_bt_cleanup);

        opt_bt_restore = new QPushButton(horizontalLayoutWidget);
        opt_bt_restore->setObjectName(QStringLiteral("opt_bt_restore"));

        verticalLayout->addWidget(opt_bt_restore);

        opt_bt_chooserev = new QPushButton(horizontalLayoutWidget);
        opt_bt_chooserev->setObjectName(QStringLiteral("opt_bt_chooserev"));

        verticalLayout->addWidget(opt_bt_chooserev);

        opt_bt_chklauncher = new QPushButton(horizontalLayoutWidget);
        opt_bt_chklauncher->setObjectName(QStringLiteral("opt_bt_chklauncher"));

        verticalLayout->addWidget(opt_bt_chklauncher);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lb_modconf = new QLabel(horizontalLayoutWidget);
        lb_modconf->setObjectName(QStringLiteral("lb_modconf"));

        verticalLayout_2->addWidget(lb_modconf);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        lb_intcolor = new QLabel(horizontalLayoutWidget);
        lb_intcolor->setObjectName(QStringLiteral("lb_intcolor"));

        verticalLayout_2->addWidget(lb_intcolor);

        colorBox = new QComboBox(horizontalLayoutWidget);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        colorBox->setEditable(false);

        verticalLayout_2->addWidget(colorBox);

        startBox = new QCheckBox(horizontalLayoutWidget);
        startBox->setObjectName(QStringLiteral("startBox"));

        verticalLayout_2->addWidget(startBox);

        checkerBox = new QCheckBox(horizontalLayoutWidget);
        checkerBox->setObjectName(QStringLiteral("checkerBox"));

        verticalLayout_2->addWidget(checkerBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        opt_bt_path = new QPushButton(horizontalLayoutWidget);
        opt_bt_path->setObjectName(QStringLiteral("opt_bt_path"));

        horizontalLayout_2->addWidget(opt_bt_path);


        verticalLayout_2->addLayout(horizontalLayout_2);

        opt_text_path = new QLineEdit(horizontalLayoutWidget);
        opt_text_path->setObjectName(QStringLiteral("opt_text_path"));
        sizePolicy.setHeightForWidth(opt_text_path->sizePolicy().hasHeightForWidth());
        opt_text_path->setSizePolicy(sizePolicy);
        opt_text_path->setMinimumSize(QSize(224, 0));
        opt_text_path->setReadOnly(true);

        verticalLayout_2->addWidget(opt_text_path);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(optionBox);

        QMetaObject::connectSlotsByName(optionBox);
    } // setupUi

    void retranslateUi(QWidget *optionBox)
    {
        optionBox->setWindowTitle(QApplication::translate("optionBox", "Options", 0));
        label_2->setText(QApplication::translate("optionBox", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Update settings :</span></p></body></html>", 0));
        opt_bt_update->setText(QApplication::translate("optionBox", "Check for update", 0));
        opt_bt_cleanup->setText(QApplication::translate("optionBox", "Clean up installation", 0));
        opt_bt_restore->setText(QApplication::translate("optionBox", "Restore previous version", 0));
        opt_bt_chooserev->setText(QApplication::translate("optionBox", "Choose a previous revision", 0));
        opt_bt_chklauncher->setText(QApplication::translate("optionBox", "Check for launcher update", 0));
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
        startBox->setText(QApplication::translate("optionBox", "Autostart the mod with the game", 0));
        checkerBox->setText(QApplication::translate("optionBox", "Close the checker on game launch", 0));
        label->setText(QApplication::translate("optionBox", "Game path :", 0));
        opt_bt_path->setText(QApplication::translate("optionBox", "Select game path", 0));
    } // retranslateUi

};

namespace Ui {
    class optionBox: public Ui_optionBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONBOX_H
