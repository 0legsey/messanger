/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonPrv;
    QLineEdit *lineEdit;
    QLineEdit *prvText;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QComboBox *userBox;
    QLabel *label;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonSend;
    QPushButton *pushButtonName;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QTextBrowser *privateBrowser;
    QSpacerItem *verticalSpacer;
    QLabel *error_label;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(857, 519);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        pushButtonPrv = new QPushButton(centralwidget);
        pushButtonPrv->setObjectName("pushButtonPrv");
        pushButtonPrv->setEnabled(false);

        gridLayout->addWidget(pushButtonPrv, 9, 0, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(false);

        gridLayout->addWidget(lineEdit, 11, 2, 1, 1);

        prvText = new QLineEdit(centralwidget);
        prvText->setObjectName("prvText");
        prvText->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(prvText->sizePolicy().hasHeightForWidth());
        prvText->setSizePolicy(sizePolicy);

        gridLayout->addWidget(prvText, 8, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 6, 0, 1, 1);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setEnabled(false);

        gridLayout->addWidget(textBrowser, 2, 2, 8, 2);

        userBox = new QComboBox(centralwidget);
        userBox->addItem(QString());
        userBox->setObjectName("userBox");
        userBox->setEnabled(false);

        gridLayout->addWidget(userBox, 11, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(false);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButtonConnect = new QPushButton(centralwidget);
        pushButtonConnect->setObjectName("pushButtonConnect");

        gridLayout->addWidget(pushButtonConnect, 0, 2, 1, 2);

        pushButtonSend = new QPushButton(centralwidget);
        pushButtonSend->setObjectName("pushButtonSend");
        pushButtonSend->setEnabled(false);

        gridLayout->addWidget(pushButtonSend, 11, 3, 1, 1);

        pushButtonName = new QPushButton(centralwidget);
        pushButtonName->setObjectName("pushButtonName");
        pushButtonName->setEnabled(false);
        pushButtonName->setCheckable(false);
        pushButtonName->setChecked(false);

        gridLayout->addWidget(pushButtonName, 3, 0, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setEnabled(false);
        lineEdit_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_2, 1, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 2, 1, 2);

        privateBrowser = new QTextBrowser(centralwidget);
        privateBrowser->setObjectName("privateBrowser");
        privateBrowser->setEnabled(false);

        gridLayout->addWidget(privateBrowser, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 1, 1, 1);

        error_label = new QLabel(centralwidget);
        error_label->setObjectName("error_label");
        error_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(error_label, 4, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 857, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonPrv->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Private chat", nullptr));
        userBox->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "Enter username", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        pushButtonSend->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
        pushButtonName->setText(QCoreApplication::translate("MainWindow", "Save username", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Global chat", nullptr));
        error_label->setText(QCoreApplication::translate("MainWindow", "Choosen name is already taken", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
