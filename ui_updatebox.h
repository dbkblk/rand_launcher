/********************************************************************************
** Form generated from reading UI file 'updatebox.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEBOX_H
#define UI_UPDATEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updatebox
{
public:
    QDialogButtonBox *bt_update;
    QTextEdit *consoleOutput;
    QLabel *lb_changelog;
    QLabel *lb_askupdate;

    void setupUi(QWidget *updatebox)
    {
        if (updatebox->objectName().isEmpty())
            updatebox->setObjectName(QStringLiteral("updatebox"));
        updatebox->resize(500, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(updatebox->sizePolicy().hasHeightForWidth());
        updatebox->setSizePolicy(sizePolicy);
        bt_update = new QDialogButtonBox(updatebox);
        bt_update->setObjectName(QStringLiteral("bt_update"));
        bt_update->setGeometry(QRect(280, 60, 156, 23));
        bt_update->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        consoleOutput = new QTextEdit(updatebox);
        consoleOutput->setObjectName(QStringLiteral("consoleOutput"));
        consoleOutput->setGeometry(QRect(20, 100, 461, 281));
        lb_changelog = new QLabel(updatebox);
        lb_changelog->setObjectName(QStringLiteral("lb_changelog"));
        lb_changelog->setGeometry(QRect(25, 73, 231, 20));
        lb_askupdate = new QLabel(updatebox);
        lb_askupdate->setObjectName(QStringLiteral("lb_askupdate"));
        lb_askupdate->setGeometry(QRect(20, 19, 461, 21));

        retranslateUi(updatebox);

        QMetaObject::connectSlotsByName(updatebox);
    } // setupUi

    void retranslateUi(QWidget *updatebox)
    {
        updatebox->setWindowTitle(QApplication::translate("updatebox", "Form", 0));
        lb_changelog->setText(QApplication::translate("updatebox", "Changelog :", 0));
        lb_askupdate->setText(QApplication::translate("updatebox", "There is an update available. Do you want to update ?", 0));
    } // retranslateUi

};

namespace Ui {
    class updatebox: public Ui_updatebox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEBOX_H
