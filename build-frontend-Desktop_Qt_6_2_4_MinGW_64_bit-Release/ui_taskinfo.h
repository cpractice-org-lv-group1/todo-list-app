/********************************************************************************
** Form generated from reading UI file 'taskinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKINFO_H
#define UI_TASKINFO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskInfo
{
public:
    QWidget *centralwidget;
    QTextEdit *TaskHeader;
    QTextEdit *TaskDescription;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QTextEdit *TaskStatus;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *EditButton;
    QPushButton *DoneButton;
    QPushButton *DeleteButton;
    QLabel *label_8;
    QLabel *NoneLabel;
    QComboBox *TaskCategory;
    QDateTimeEdit *TaskExpEnd;
    QDateTimeEdit *TaskEnd;
    QDateTimeEdit *TaskStartTime;
    QPushButton *DoneButton_2;
    QLabel *DonePoints;
    QLabel *DonePoints_2;
    QComboBox *TaskDifficulty;
    QLabel *TimeError;
    QLabel *BodyError;
    QLabel *HeaderError;

    void setupUi(QMainWindow *TaskInfo)
    {
        if (TaskInfo->objectName().isEmpty())
            TaskInfo->setObjectName(QString::fromUtf8("TaskInfo"));
        TaskInfo->resize(590, 309);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        TaskInfo->setWindowIcon(icon);
        TaskInfo->setStyleSheet(QString::fromUtf8("QTextEdit {border: 1px solid black; } \n"
"QDateEdit {border: 1px solid black; } \n"
""));
        centralwidget = new QWidget(TaskInfo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        TaskHeader = new QTextEdit(centralwidget);
        TaskHeader->setObjectName(QString::fromUtf8("TaskHeader"));
        TaskHeader->setGeometry(QRect(10, 20, 375, 41));
        TaskHeader->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TaskHeader->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TaskDescription = new QTextEdit(centralwidget);
        TaskDescription->setObjectName(QString::fromUtf8("TaskDescription"));
        TaskDescription->setGeometry(QRect(10, 80, 375, 71));
        TaskDescription->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TaskDescription->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 61, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 160, 61, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(205, 160, 101, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(395, 160, 61, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(395, 230, 61, 16));
        TaskStatus = new QTextEdit(centralwidget);
        TaskStatus->setObjectName(QString::fromUtf8("TaskStatus"));
        TaskStatus->setGeometry(QRect(396, 250, 181, 41));
        TaskStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TaskStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(205, 230, 61, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 230, 61, 16));
        EditButton = new QPushButton(centralwidget);
        EditButton->setObjectName(QString::fromUtf8("EditButton"));
        EditButton->setGeometry(QRect(400, 10, 81, 41));
        EditButton->setCursor(QCursor(Qt::PointingHandCursor));
        EditButton->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid blue;}"));
        DoneButton = new QPushButton(centralwidget);
        DoneButton->setObjectName(QString::fromUtf8("DoneButton"));
        DoneButton->setGeometry(QRect(400, 60, 131, 41));
        DoneButton->setCursor(QCursor(Qt::PointingHandCursor));
        DoneButton->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid darkgreen;}"));
        DeleteButton = new QPushButton(centralwidget);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        DeleteButton->setGeometry(QRect(500, 10, 81, 41));
        DeleteButton->setCursor(QCursor(Qt::PointingHandCursor));
        DeleteButton->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid red;}"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 0, 61, 16));
        NoneLabel = new QLabel(centralwidget);
        NoneLabel->setObjectName(QString::fromUtf8("NoneLabel"));
        NoneLabel->setGeometry(QRect(400, 190, 49, 16));
        TaskCategory = new QComboBox(centralwidget);
        TaskCategory->setObjectName(QString::fromUtf8("TaskCategory"));
        TaskCategory->setGeometry(QRect(205, 250, 181, 41));
        TaskCategory->setCursor(QCursor(Qt::PointingHandCursor));
        TaskExpEnd = new QDateTimeEdit(centralwidget);
        TaskExpEnd->setObjectName(QString::fromUtf8("TaskExpEnd"));
        TaskExpEnd->setGeometry(QRect(205, 180, 181, 41));
        QFont font;
        font.setPointSize(14);
        TaskExpEnd->setFont(font);
        TaskExpEnd->setButtonSymbols(QAbstractSpinBox::NoButtons);
        TaskEnd = new QDateTimeEdit(centralwidget);
        TaskEnd->setObjectName(QString::fromUtf8("TaskEnd"));
        TaskEnd->setGeometry(QRect(395, 180, 181, 41));
        TaskEnd->setFont(font);
        TaskEnd->setButtonSymbols(QAbstractSpinBox::NoButtons);
        TaskStartTime = new QDateTimeEdit(centralwidget);
        TaskStartTime->setObjectName(QString::fromUtf8("TaskStartTime"));
        TaskStartTime->setGeometry(QRect(10, 180, 181, 41));
        TaskStartTime->setFont(font);
        TaskStartTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
        DoneButton_2 = new QPushButton(centralwidget);
        DoneButton_2->setObjectName(QString::fromUtf8("DoneButton_2"));
        DoneButton_2->setGeometry(QRect(400, 110, 131, 41));
        DoneButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        DoneButton_2->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid darkgreen;}"));
        DonePoints = new QLabel(centralwidget);
        DonePoints->setObjectName(QString::fromUtf8("DonePoints"));
        DonePoints->setGeometry(QRect(540, 60, 49, 41));
        DonePoints_2 = new QLabel(centralwidget);
        DonePoints_2->setObjectName(QString::fromUtf8("DonePoints_2"));
        DonePoints_2->setGeometry(QRect(540, 110, 49, 41));
        TaskDifficulty = new QComboBox(centralwidget);
        TaskDifficulty->setObjectName(QString::fromUtf8("TaskDifficulty"));
        TaskDifficulty->setGeometry(QRect(10, 250, 181, 41));
        TaskDifficulty->setCursor(QCursor(Qt::PointingHandCursor));
        TimeError = new QLabel(centralwidget);
        TimeError->setObjectName(QString::fromUtf8("TimeError"));
        TimeError->setGeometry(QRect(68, 160, 131, 16));
        BodyError = new QLabel(centralwidget);
        BodyError->setObjectName(QString::fromUtf8("BodyError"));
        BodyError->setGeometry(QRect(263, 60, 121, 16));
        HeaderError = new QLabel(centralwidget);
        HeaderError->setObjectName(QString::fromUtf8("HeaderError"));
        HeaderError->setGeometry(QRect(263, 0, 121, 16));
        TaskInfo->setCentralWidget(centralwidget);

        retranslateUi(TaskInfo);

        QMetaObject::connectSlotsByName(TaskInfo);
    } // setupUi

    void retranslateUi(QMainWindow *TaskInfo)
    {
        TaskInfo->setWindowTitle(QCoreApplication::translate("TaskInfo", "Task Information", nullptr));
        label->setText(QCoreApplication::translate("TaskInfo", "Description", nullptr));
        label_2->setText(QCoreApplication::translate("TaskInfo", "Start time", nullptr));
        label_3->setText(QCoreApplication::translate("TaskInfo", "Expected end time", nullptr));
        label_4->setText(QCoreApplication::translate("TaskInfo", "End time", nullptr));
        label_5->setText(QCoreApplication::translate("TaskInfo", "Status", nullptr));
        label_6->setText(QCoreApplication::translate("TaskInfo", "Category", nullptr));
        label_7->setText(QCoreApplication::translate("TaskInfo", "Difficulty", nullptr));
        EditButton->setText(QCoreApplication::translate("TaskInfo", "Edit", nullptr));
        DoneButton->setText(QCoreApplication::translate("TaskInfo", "Mark as done", nullptr));
        DeleteButton->setText(QCoreApplication::translate("TaskInfo", "Delete", nullptr));
        label_8->setText(QCoreApplication::translate("TaskInfo", "Header", nullptr));
        NoneLabel->setText(QCoreApplication::translate("TaskInfo", "None", nullptr));
        DoneButton_2->setText(QCoreApplication::translate("TaskInfo", "Mark as partially done", nullptr));
        DonePoints->setText(QCoreApplication::translate("TaskInfo", "Points:", nullptr));
        DonePoints_2->setText(QCoreApplication::translate("TaskInfo", "Points:", nullptr));
        TimeError->setText(QCoreApplication::translate("TaskInfo", "Start time >= End time!", nullptr));
        BodyError->setText(QCoreApplication::translate("TaskInfo", "Field cannot be empty!", nullptr));
        HeaderError->setText(QCoreApplication::translate("TaskInfo", "Field cannot be empty!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskInfo: public Ui_TaskInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKINFO_H
