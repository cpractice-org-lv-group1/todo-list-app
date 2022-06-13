/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QWidget *centralwidget;
    QTextEdit *LogEmail;
    QTextEdit *LogPass;
    QLabel *label;
    QPushButton *pushButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(800, 389);
        centralwidget = new QWidget(Registration);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LogEmail = new QTextEdit(centralwidget);
        LogEmail->setObjectName(QString::fromUtf8("LogEmail"));
        LogEmail->setGeometry(QRect(260, 100, 281, 70));
        LogPass = new QTextEdit(centralwidget);
        LogPass->setObjectName(QString::fromUtf8("LogPass"));
        LogPass->setGeometry(QRect(260, 190, 281, 70));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(330, 20, 151, 61));
        QFont font;
        font.setPointSize(26);
        label->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(350, 290, 101, 41));
        Registration->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Registration);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Registration->setStatusBar(statusbar);

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QMainWindow *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Registration", nullptr));
        label->setText(QCoreApplication::translate("Registration", "Welcome", nullptr));
        pushButton->setText(QCoreApplication::translate("Registration", "Log In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
