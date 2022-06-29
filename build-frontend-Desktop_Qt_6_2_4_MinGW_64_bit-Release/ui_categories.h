/********************************************************************************
** Form generated from reading UI file 'categories.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATEGORIES_H
#define UI_CATEGORIES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Categories
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QPushButton *EditButton;
    QPushButton *DeleteButton;
    QPushButton *AddNewButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *SetButton;

    void setupUi(QMainWindow *Categories)
    {
        if (Categories->objectName().isEmpty())
            Categories->setObjectName(QString::fromUtf8("Categories"));
        Categories->resize(369, 278);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Categories->setWindowIcon(icon);
        centralwidget = new QWidget(Categories);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 191, 261));
        QFont font;
        font.setPointSize(14);
        listWidget->setFont(font);
        EditButton = new QPushButton(centralwidget);
        EditButton->setObjectName(QString::fromUtf8("EditButton"));
        EditButton->setGeometry(QRect(210, 60, 151, 41));
        DeleteButton = new QPushButton(centralwidget);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        DeleteButton->setGeometry(QRect(210, 110, 151, 41));
        AddNewButton = new QPushButton(centralwidget);
        AddNewButton->setObjectName(QString::fromUtf8("AddNewButton"));
        AddNewButton->setGeometry(QRect(210, 230, 151, 41));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 180, 151, 41));
        lineEdit->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 160, 111, 16));
        label->setStyleSheet(QString::fromUtf8(""));
        SetButton = new QPushButton(centralwidget);
        SetButton->setObjectName(QString::fromUtf8("SetButton"));
        SetButton->setGeometry(QRect(210, 10, 151, 41));
        Categories->setCentralWidget(centralwidget);

        retranslateUi(Categories);

        QMetaObject::connectSlotsByName(Categories);
    } // setupUi

    void retranslateUi(QMainWindow *Categories)
    {
        Categories->setWindowTitle(QCoreApplication::translate("Categories", "Categories", nullptr));
        EditButton->setText(QCoreApplication::translate("Categories", "Edit", nullptr));
        DeleteButton->setText(QCoreApplication::translate("Categories", "Delete", nullptr));
        AddNewButton->setText(QCoreApplication::translate("Categories", "Add", nullptr));
        label->setText(QCoreApplication::translate("Categories", "Enter new category:", nullptr));
        SetButton->setText(QCoreApplication::translate("Categories", "Set as current", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Categories: public Ui_Categories {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATEGORIES_H
