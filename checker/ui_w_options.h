/********************************************************************************
** Form generated from reading UI file 'w_options.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_OPTIONS_H
#define UI_W_OPTIONS_H

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

class Ui_w_options
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *lb_modconf;
    QCheckBox *opt_checkbox_formations;
    QCheckBox *opt_checkbox_bluemarble;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_intcolor;
    QComboBox *colorBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *opt_bt_path;
    QLineEdit *opt_text_path;
    QSpacerItem *verticalSpacer;
    QLabel *lb_modconf_2;
    QCheckBox *checkerBox;
    QCheckBox *startBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lb_behavior;
    QComboBox *opt_updateBehavior;

    void setupUi(QWidget *w_options)
    {
        if (w_options->objectName().isEmpty())
            w_options->setObjectName(QStringLiteral("w_options"));
        w_options->setWindowModality(Qt::WindowModal);
        w_options->resize(450, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(w_options->sizePolicy().hasHeightForWidth());
        w_options->setSizePolicy(sizePolicy);
        w_options->setMinimumSize(QSize(450, 300));
        w_options->setMaximumSize(QSize(450, 300));
        w_options->setFocusPolicy(Qt::StrongFocus);
        w_options->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayoutWidget = new QWidget(w_options);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 13, 431, 278));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(10, 0, 10, 0);
        lb_modconf = new QLabel(verticalLayoutWidget);
        lb_modconf->setObjectName(QStringLiteral("lb_modconf"));

        verticalLayout_4->addWidget(lb_modconf);

        opt_checkbox_formations = new QCheckBox(verticalLayoutWidget);
        opt_checkbox_formations->setObjectName(QStringLiteral("opt_checkbox_formations"));

        verticalLayout_4->addWidget(opt_checkbox_formations);

        opt_checkbox_bluemarble = new QCheckBox(verticalLayoutWidget);
        opt_checkbox_bluemarble->setObjectName(QStringLiteral("opt_checkbox_bluemarble"));

        verticalLayout_4->addWidget(opt_checkbox_bluemarble);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lb_intcolor = new QLabel(verticalLayoutWidget);
        lb_intcolor->setObjectName(QStringLiteral("lb_intcolor"));

        horizontalLayout->addWidget(lb_intcolor);

        colorBox = new QComboBox(verticalLayoutWidget);
        colorBox->setObjectName(QStringLiteral("colorBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorBox->sizePolicy().hasHeightForWidth());
        colorBox->setSizePolicy(sizePolicy1);
        colorBox->setMinimumSize(QSize(175, 25));

        horizontalLayout->addWidget(colorBox);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        opt_bt_path = new QPushButton(verticalLayoutWidget);
        opt_bt_path->setObjectName(QStringLiteral("opt_bt_path"));
        sizePolicy1.setHeightForWidth(opt_bt_path->sizePolicy().hasHeightForWidth());
        opt_bt_path->setSizePolicy(sizePolicy1);
        opt_bt_path->setMinimumSize(QSize(175, 25));
        opt_bt_path->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(opt_bt_path);


        verticalLayout_4->addLayout(horizontalLayout_2);

        opt_text_path = new QLineEdit(verticalLayoutWidget);
        opt_text_path->setObjectName(QStringLiteral("opt_text_path"));
        sizePolicy1.setHeightForWidth(opt_text_path->sizePolicy().hasHeightForWidth());
        opt_text_path->setSizePolicy(sizePolicy1);
        opt_text_path->setMinimumSize(QSize(224, 25));
        opt_text_path->setMaximumSize(QSize(475, 16777215));
        opt_text_path->setReadOnly(true);

        verticalLayout_4->addWidget(opt_text_path);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer);

        lb_modconf_2 = new QLabel(verticalLayoutWidget);
        lb_modconf_2->setObjectName(QStringLiteral("lb_modconf_2"));

        verticalLayout_4->addWidget(lb_modconf_2);

        checkerBox = new QCheckBox(verticalLayoutWidget);
        checkerBox->setObjectName(QStringLiteral("checkerBox"));

        verticalLayout_4->addWidget(checkerBox);

        startBox = new QCheckBox(verticalLayoutWidget);
        startBox->setObjectName(QStringLiteral("startBox"));

        verticalLayout_4->addWidget(startBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lb_behavior = new QLabel(verticalLayoutWidget);
        lb_behavior->setObjectName(QStringLiteral("lb_behavior"));

        horizontalLayout_3->addWidget(lb_behavior);

        opt_updateBehavior = new QComboBox(verticalLayoutWidget);
        opt_updateBehavior->setObjectName(QStringLiteral("opt_updateBehavior"));
        sizePolicy1.setHeightForWidth(opt_updateBehavior->sizePolicy().hasHeightForWidth());
        opt_updateBehavior->setSizePolicy(sizePolicy1);
        opt_updateBehavior->setMinimumSize(QSize(175, 25));

        horizontalLayout_3->addWidget(opt_updateBehavior);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(w_options);

        QMetaObject::connectSlotsByName(w_options);
    } // setupUi

    void retranslateUi(QWidget *w_options)
    {
        w_options->setWindowTitle(QApplication::translate("w_options", "Options", 0));
        lb_modconf->setText(QApplication::translate("w_options", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Mod configuration :</span></p></body></html>", 0));
        opt_checkbox_formations->setText(QApplication::translate("w_options", "Enable formations (more graphical units)", 0));
        opt_checkbox_bluemarble->setText(QApplication::translate("w_options", "Enable Blue Marble (alternative terrain graphics)", 0));
        lb_intcolor->setText(QApplication::translate("w_options", "Interface color:", 0));
        colorBox->clear();
        colorBox->insertItems(0, QStringList()
         << QApplication::translate("w_options", "Black", 0)
         << QApplication::translate("w_options", "Coal", 0)
         << QApplication::translate("w_options", "Dark red", 0)
         << QApplication::translate("w_options", "Forest", 0)
         << QApplication::translate("w_options", "Purple", 0)
         << QApplication::translate("w_options", "Red", 0)
         << QApplication::translate("w_options", "Silver", 0)
         << QApplication::translate("w_options", "Cerulean", 0)
        );
        label->setText(QApplication::translate("w_options", "Game path:", 0));
        opt_bt_path->setText(QApplication::translate("w_options", "Select game path", 0));
        lb_modconf_2->setText(QApplication::translate("w_options", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Launcher configuration :</span></p></body></html>", 0));
        checkerBox->setText(QApplication::translate("w_options", "Close the launcher when game start", 0));
        startBox->setText(QApplication::translate("w_options", "Autostart the mod with the game", 0));
        lb_behavior->setText(QApplication::translate("w_options", "Behavior on update:", 0));
        opt_updateBehavior->clear();
        opt_updateBehavior->insertItems(0, QStringList()
         << QApplication::translate("w_options", "Use new files (default)", 0)
         << QApplication::translate("w_options", "Keep local changes", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class w_options: public Ui_w_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_OPTIONS_H
