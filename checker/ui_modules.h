/********************************************************************************
** Form generated from reading UI file 'modules.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULES_H
#define UI_MODULES_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_modules
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *tree_list;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *changelog_box;
    QVBoxLayout *verticalLayout;
    QLabel *label_core_version;
    QSpacerItem *verticalSpacer;
    QPushButton *bt_update;
    QPushButton *bt_remove;

    void setupUi(QMainWindow *modules)
    {
        if (modules->objectName().isEmpty())
            modules->setObjectName(QStringLiteral("modules"));
        modules->resize(600, 300);
        centralwidget = new QWidget(modules);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tree_list = new QTreeWidget(centralwidget);
        tree_list->setObjectName(QStringLiteral("tree_list"));

        horizontalLayout->addWidget(tree_list);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        changelog_box = new QTextEdit(centralwidget);
        changelog_box->setObjectName(QStringLiteral("changelog_box"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(changelog_box->sizePolicy().hasHeightForWidth());
        changelog_box->setSizePolicy(sizePolicy);
        changelog_box->setMinimumSize(QSize(300, 0));
        changelog_box->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        changelog_box->setAutoFormatting(QTextEdit::AutoAll);
        changelog_box->setReadOnly(true);
        changelog_box->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>"));
        changelog_box->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_2->addWidget(changelog_box);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_core_version = new QLabel(centralwidget);
        label_core_version->setObjectName(QStringLiteral("label_core_version"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_core_version->sizePolicy().hasHeightForWidth());
        label_core_version->setSizePolicy(sizePolicy1);
        label_core_version->setMinimumSize(QSize(70, 70));
        label_core_version->setStyleSheet(QLatin1String("border-color: rgb(255, 255, 0);\n"
"\n"
"font: 75 9pt \"MS Shell Dlg 2\";"));
        label_core_version->setText(QStringLiteral("TextLabel"));
        label_core_version->setAlignment(Qt::AlignCenter);
        label_core_version->setWordWrap(true);

        verticalLayout->addWidget(label_core_version);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        bt_update = new QPushButton(centralwidget);
        bt_update->setObjectName(QStringLiteral("bt_update"));
        sizePolicy1.setHeightForWidth(bt_update->sizePolicy().hasHeightForWidth());
        bt_update->setSizePolicy(sizePolicy1);
        bt_update->setMinimumSize(QSize(70, 60));
        bt_update->setText(QStringLiteral("bt_update"));

        verticalLayout->addWidget(bt_update);

        bt_remove = new QPushButton(centralwidget);
        bt_remove->setObjectName(QStringLiteral("bt_remove"));
        sizePolicy1.setHeightForWidth(bt_remove->sizePolicy().hasHeightForWidth());
        bt_remove->setSizePolicy(sizePolicy1);
        bt_remove->setMinimumSize(QSize(70, 60));
        bt_remove->setText(QStringLiteral("bt_remove"));

        verticalLayout->addWidget(bt_remove);


        horizontalLayout->addLayout(verticalLayout);

        modules->setCentralWidget(centralwidget);

        retranslateUi(modules);

        QMetaObject::connectSlotsByName(modules);
    } // setupUi

    void retranslateUi(QMainWindow *modules)
    {
        modules->setWindowTitle(QApplication::translate("modules", "MainWindow", 0));
        QTreeWidgetItem *___qtreewidgetitem = tree_list->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("modules", "Components", 0));
        label->setText(QApplication::translate("modules", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Changes:</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class modules: public Ui_modules {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULES_H
