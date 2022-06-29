/********************************************************************************
** Form generated from reading UI file 'addfriend.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIEND_H
#define UI_ADDFRIEND_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriend
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *Error;
    QPushButton *pushButton;

    void setupUi(QMainWindow *AddFriend)
    {
        if (AddFriend->objectName().isEmpty())
            AddFriend->setObjectName(QString::fromUtf8("AddFriend"));
        AddFriend->resize(243, 130);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        AddFriend->setWindowIcon(icon);
        centralwidget = new QWidget(AddFriend);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 221, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 111, 16));
        Error = new QLabel(centralwidget);
        Error->setObjectName(QString::fromUtf8("Error"));
        Error->setGeometry(QRect(110, 10, 121, 16));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 80, 111, 41));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        AddFriend->setCentralWidget(centralwidget);

        retranslateUi(AddFriend);

        QMetaObject::connectSlotsByName(AddFriend);
    } // setupUi

    void retranslateUi(QMainWindow *AddFriend)
    {
        AddFriend->setWindowTitle(QCoreApplication::translate("AddFriend", "Add Friend", nullptr));
        label->setText(QCoreApplication::translate("AddFriend", "Enter friend email:", nullptr));
        Error->setText(QCoreApplication::translate("AddFriend", "Field cannot be empty!", nullptr));
        pushButton->setText(QCoreApplication::translate("AddFriend", "Send request", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriend: public Ui_AddFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIEND_H
