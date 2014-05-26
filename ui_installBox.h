/********************************************************************************
** Form generated from reading UI file 'installBox.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALLBOX_H
#define UI_INSTALLBOX_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_installBox
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *installBox)
    {
        if (installBox->objectName().isEmpty())
            installBox->setObjectName(QStringLiteral("installBox"));
        installBox->resize(300, 150);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(installBox->sizePolicy().hasHeightForWidth());
        installBox->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(installBox);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 102, 281, 31));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Yes);
        buttonBox->setCenterButtons(true);
        label = new QLabel(installBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 301, 81));

        retranslateUi(installBox);
        QObject::connect(buttonBox, SIGNAL(accepted()), installBox, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), installBox, SLOT(reject()));

        QMetaObject::connectSlotsByName(installBox);
    } // setupUi

    void retranslateUi(QDialog *installBox)
    {
        installBox->setWindowTitle(QApplication::translate("installBox", "Mod installation", 0));
        label->setText(QApplication::translate("installBox", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600;\">A New Dawn 2 : </span></p><p align=\"center\"><span style=\" font-size:9pt;\">The mod is not installed.</span></p><p align=\"center\"><span style=\" font-size:9pt;\">Do you want to download and install it ?</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class installBox: public Ui_installBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALLBOX_H
