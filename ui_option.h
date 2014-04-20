/********************************************************************************
** Form generated from reading UI file 'option.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTION_H
#define UI_OPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPushButton *cleanupButton;
    QPushButton *revertButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *colorBox;
    QLabel *label_5;
    QPushButton *autostartButton;
    QPushButton *pushButton_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 481, 142));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(label_2);

        cleanupButton = new QPushButton(layoutWidget);
        cleanupButton->setObjectName(QStringLiteral("cleanupButton"));

        verticalLayout_2->addWidget(cleanupButton);

        revertButton = new QPushButton(layoutWidget);
        revertButton->setObjectName(QStringLiteral("revertButton"));

        verticalLayout_2->addWidget(revertButton);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        colorBox = new QComboBox(layoutWidget);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        colorBox->setEditable(false);

        verticalLayout->addWidget(colorBox);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        autostartButton = new QPushButton(layoutWidget);
        autostartButton->setObjectName(QStringLiteral("autostartButton"));

        verticalLayout->addWidget(autostartButton);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "installBox", 0));
        label_2->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600;\">Update process</span></p></body></html>", 0));
        cleanupButton->setText(QApplication::translate("Dialog", "Clean up the installation", 0));
        revertButton->setText(QApplication::translate("Dialog", "Revert to previous version", 0));
        label_3->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Mod configuration</span></p></body></html>", 0));
        label_4->setText(QApplication::translate("Dialog", "Change interface color :", 0));
        colorBox->clear();
        colorBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "Black", 0)
         << QApplication::translate("Dialog", "Coal", 0)
         << QApplication::translate("Dialog", "Dark Red", 0)
         << QApplication::translate("Dialog", "Forest", 0)
         << QApplication::translate("Dialog", "Purple", 0)
         << QApplication::translate("Dialog", "Red", 0)
         << QApplication::translate("Dialog", "Silver", 0)
         << QApplication::translate("Dialog", "Cerulean", 0)
        );
        label_5->setText(QApplication::translate("Dialog", "Change startup settings :", 0));
        autostartButton->setText(QApplication::translate("Dialog", "Launch the mod by default", 0));
        pushButton_4->setText(QApplication::translate("Dialog", "Restore default config.", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTION_H
