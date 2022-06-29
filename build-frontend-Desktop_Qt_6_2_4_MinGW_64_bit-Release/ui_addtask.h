/********************************************************************************
** Form generated from reading UI file 'addtask.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTASK_H
#define UI_ADDTASK_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTask
{
public:
    QWidget *centralwidget;
    QLineEdit *Header;
    QTextEdit *Body;
    QDateTimeEdit *StartTime;
    QDateTimeEdit *ExpEndTime;
    QComboBox *Category;
    QPushButton *AddButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *Difficulty;
    QLabel *EndTimeError;
    QLabel *DescriptionError;
    QLabel *HeaderError;

    void setupUi(QMainWindow *AddTask)
    {
        if (AddTask->objectName().isEmpty())
            AddTask->setObjectName(QString::fromUtf8("AddTask"));
        AddTask->resize(240, 409);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        AddTask->setWindowIcon(icon);
        centralwidget = new QWidget(AddTask);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Header = new QLineEdit(centralwidget);
        Header->setObjectName(QString::fromUtf8("Header"));
        Header->setGeometry(QRect(10, 20, 221, 41));
        Body = new QTextEdit(centralwidget);
        Body->setObjectName(QString::fromUtf8("Body"));
        Body->setGeometry(QRect(10, 90, 221, 71));
        StartTime = new QDateTimeEdit(centralwidget);
        StartTime->setObjectName(QString::fromUtf8("StartTime"));
        StartTime->setGeometry(QRect(10, 185, 221, 41));
        StartTime->setAlignment(Qt::AlignCenter);
        StartTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ExpEndTime = new QDateTimeEdit(centralwidget);
        ExpEndTime->setObjectName(QString::fromUtf8("ExpEndTime"));
        ExpEndTime->setGeometry(QRect(10, 245, 221, 41));
        ExpEndTime->setCursor(QCursor(Qt::ArrowCursor));
        ExpEndTime->setAlignment(Qt::AlignCenter);
        ExpEndTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Category = new QComboBox(centralwidget);
        Category->setObjectName(QString::fromUtf8("Category"));
        Category->setGeometry(QRect(10, 308, 151, 41));
        Category->setCursor(QCursor(Qt::PointingHandCursor));
        AddButton = new QPushButton(centralwidget);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));
        AddButton->setGeometry(QRect(70, 360, 91, 41));
        AddButton->setCursor(QCursor(Qt::PointingHandCursor));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 2, 41, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 61, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 168, 61, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 229, 61, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 290, 61, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(170, 290, 61, 16));
        Difficulty = new QComboBox(centralwidget);
        Difficulty->setObjectName(QString::fromUtf8("Difficulty"));
        Difficulty->setGeometry(QRect(170, 308, 61, 41));
        Difficulty->setCursor(QCursor(Qt::PointingHandCursor));
        EndTimeError = new QLabel(centralwidget);
        EndTimeError->setObjectName(QString::fromUtf8("EndTimeError"));
        EndTimeError->setGeometry(QRect(107, 228, 131, 20));
        DescriptionError = new QLabel(centralwidget);
        DescriptionError->setObjectName(QString::fromUtf8("DescriptionError"));
        DescriptionError->setGeometry(QRect(110, 70, 131, 20));
        HeaderError = new QLabel(centralwidget);
        HeaderError->setObjectName(QString::fromUtf8("HeaderError"));
        HeaderError->setGeometry(QRect(110, 2, 131, 20));
        AddTask->setCentralWidget(centralwidget);

        retranslateUi(AddTask);

        QMetaObject::connectSlotsByName(AddTask);
    } // setupUi

    void retranslateUi(QMainWindow *AddTask)
    {
        AddTask->setWindowTitle(QCoreApplication::translate("AddTask", "Add Task", nullptr));
        AddButton->setText(QCoreApplication::translate("AddTask", "Add", nullptr));
        label->setText(QCoreApplication::translate("AddTask", "Header", nullptr));
        label_2->setText(QCoreApplication::translate("AddTask", "Description", nullptr));
        label_3->setText(QCoreApplication::translate("AddTask", "Start time", nullptr));
        label_4->setText(QCoreApplication::translate("AddTask", "End time", nullptr));
        label_5->setText(QCoreApplication::translate("AddTask", "Category", nullptr));
        label_6->setText(QCoreApplication::translate("AddTask", "Difficulty", nullptr));
        EndTimeError->setText(QCoreApplication::translate("AddTask", "End time <= Start time!", nullptr));
        DescriptionError->setText(QCoreApplication::translate("AddTask", "Field cannot be empty!", nullptr));
        HeaderError->setText(QCoreApplication::translate("AddTask", "Field cannot be empty!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTask: public Ui_AddTask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTASK_H
