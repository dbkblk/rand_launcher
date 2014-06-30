/********************************************************************************
** Form generated from reading UI file 'w_install.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_INSTALL_H
#define UI_W_INSTALL_H

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

class Ui_w_install
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *w_install)
    {
        if (w_install->objectName().isEmpty())
            w_install->setObjectName(QStringLiteral("w_install"));
        w_install->resize(300, 150);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(w_install->sizePolicy().hasHeightForWidth());
        w_install->setSizePolicy(sizePolicy);
        w_install->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox = new QDialogButtonBox(w_install);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 102, 281, 31));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Yes);
        buttonBox->setCenterButtons(true);
        label = new QLabel(w_install);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 301, 81));

        retranslateUi(w_install);
        QObject::connect(buttonBox, SIGNAL(accepted()), w_install, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), w_install, SLOT(reject()));

        QMetaObject::connectSlotsByName(w_install);
    } // setupUi

    void retranslateUi(QDialog *w_install)
    {
        w_install->setWindowTitle(QApplication::translate("w_install", "Mod installation", 0));
        label->setText(QApplication::translate("w_install", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600;\">A New Dawn : </span></p><p align=\"center\"><span style=\" font-size:9pt;\">The mod is not installed.</span></p><p align=\"center\"><span style=\" font-size:9pt;\">Do you want to download and install it ?</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class w_install: public Ui_w_install {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_INSTALL_H
