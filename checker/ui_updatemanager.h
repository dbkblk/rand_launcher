/********************************************************************************
** Form generated from reading UI file 'updatemanager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEMANAGER_H
#define UI_UPDATEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updateManager
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *updateManager)
    {
        if (updateManager->objectName().isEmpty())
            updateManager->setObjectName(QStringLiteral("updateManager"));
        updateManager->resize(550, 300);
        updateManager->setWindowTitle(QStringLiteral("Form"));
        tableWidget = new QTableWidget(updateManager);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setText(QStringLiteral("Installed"));
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setText(QStringLiteral("Mod"));
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setText(QStringLiteral("Launcher"));
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setText(QStringLiteral("Addon 1"));
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 531, 281));
        tableWidget->horizontalHeader()->setDefaultSectionSize(125);
        tableWidget->horizontalHeader()->setMinimumSectionSize(100);
        pushButton = new QPushButton(updateManager);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(314, 410, 171, 23));
        pushButton_2 = new QPushButton(updateManager);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 410, 75, 23));

        retranslateUi(updateManager);

        QMetaObject::connectSlotsByName(updateManager);
    } // setupUi

    void retranslateUi(QWidget *updateManager)
    {

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QApplication::translate("updateManager", "Update selected components", 0));
        pushButton_2->setText(QApplication::translate("updateManager", "Cancel", 0));
        Q_UNUSED(updateManager);
    } // retranslateUi

};

namespace Ui {
    class updateManager: public Ui_updateManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEMANAGER_H
