/********************************************************************************
** Form generated from reading UI file 'task_updater.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_UPDATER_H
#define UI_TASK_UPDATER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task_updater
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;
    QTextEdit *console_output;

    void setupUi(QMainWindow *task_updater)
    {
        if (task_updater->objectName().isEmpty())
            task_updater->setObjectName(QStringLiteral("task_updater"));
        task_updater->resize(600, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(task_updater->sizePolicy().hasHeightForWidth());
        task_updater->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(task_updater);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setFormat(QStringLiteral("%p%"));

        verticalLayout->addWidget(progressBar);

        console_output = new QTextEdit(centralwidget);
        console_output->setObjectName(QStringLiteral("console_output"));
        console_output->setAutoFormatting(QTextEdit::AutoAll);
        console_output->setReadOnly(true);
        console_output->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>"));
        console_output->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(console_output);

        task_updater->setCentralWidget(centralwidget);

        retranslateUi(task_updater);

        QMetaObject::connectSlotsByName(task_updater);
    } // setupUi

    void retranslateUi(QMainWindow *task_updater)
    {
        task_updater->setWindowTitle(QApplication::translate("task_updater", "Module updater", 0));
        label->setText(QApplication::translate("task_updater", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class task_updater: public Ui_task_updater {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_UPDATER_H
