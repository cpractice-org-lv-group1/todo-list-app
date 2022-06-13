/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(800, 414);
        centralwidget = new QWidget(Form);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(330, 270, 80, 24));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(340, 130, 49, 16));
        Form->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Form);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Form->setStatusBar(statusbar);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QMainWindow *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "Go back", nullptr));
        label->setText(QCoreApplication::translate("Form", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
