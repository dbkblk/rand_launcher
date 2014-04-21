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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optionBox
{
public:
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *colorBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *opt_bt_update;
    QPushButton *opt_bt_cleanup;
    QPushButton *opt_bt_restore;
    QPushButton *opt_bt_chooserev;
    QCheckBox *startBox;

    void setupUi(QWidget *optionBox)
    {
        if (optionBox->objectName().isEmpty())
            optionBox->setObjectName(QStringLiteral("optionBox"));
        optionBox->resize(500, 250);
        optionBox->setFocusPolicy(Qt::StrongFocus);
        optionBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        label_2 = new QLabel(optionBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 91, 21));
        label_3 = new QLabel(optionBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(180, 70, 91, 21));
        label_4 = new QLabel(optionBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(180, 130, 91, 21));
        colorBox = new QComboBox(optionBox);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        colorBox->setGeometry(QRect(180, 160, 141, 23));
        colorBox->setEditable(false);
        verticalLayoutWidget = new QWidget(optionBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 100, 160, 112));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        opt_bt_update = new QPushButton(verticalLayoutWidget);
        opt_bt_update->setObjectName(QStringLiteral("opt_bt_update"));

        verticalLayout->addWidget(opt_bt_update);

        opt_bt_cleanup = new QPushButton(verticalLayoutWidget);
        opt_bt_cleanup->setObjectName(QStringLiteral("opt_bt_cleanup"));

        verticalLayout->addWidget(opt_bt_cleanup);

        opt_bt_restore = new QPushButton(verticalLayoutWidget);
        opt_bt_restore->setObjectName(QStringLiteral("opt_bt_restore"));

        verticalLayout->addWidget(opt_bt_restore);

        opt_bt_chooserev = new QPushButton(verticalLayoutWidget);
        opt_bt_chooserev->setObjectName(QStringLiteral("opt_bt_chooserev"));

        verticalLayout->addWidget(opt_bt_chooserev);

        startBox = new QCheckBox(optionBox);
        startBox->setObjectName(QStringLiteral("startBox"));
        startBox->setGeometry(QRect(180, 190, 191, 21));

        retranslateUi(optionBox);

        QMetaObject::connectSlotsByName(optionBox);
    } // setupUi

    void retranslateUi(QWidget *optionBox)
    {
        optionBox->setWindowTitle(QApplication::translate("optionBox", "Options", 0));
        label_2->setText(QApplication::translate("optionBox", "Update settings:", 0));
        label_3->setText(QApplication::translate("optionBox", "Mod configuration", 0));
        label_4->setText(QApplication::translate("optionBox", "Interface color", 0));
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
        opt_bt_update->setText(QApplication::translate("optionBox", "Check for update", 0));
        opt_bt_cleanup->setText(QApplication::translate("optionBox", "Clean up installation", 0));
        opt_bt_restore->setText(QApplication::translate("optionBox", "Restore previous version", 0));
        opt_bt_chooserev->setText(QApplication::translate("optionBox", "Choose a previous revision", 0));
        startBox->setText(QApplication::translate("optionBox", "Autostart the mod with the game", 0));
    } // retranslateUi

};

namespace Ui {
    class optionBox: public Ui_optionBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONBOX_H
