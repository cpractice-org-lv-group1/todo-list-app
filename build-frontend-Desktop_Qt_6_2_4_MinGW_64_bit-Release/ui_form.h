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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QListWidget *Friendlist;
    QLabel *friendlabel;
    QLabel *labelName;
    QLabel *RankImg;
    QLabel *labelPoints;
    QPushButton *ArchiveButton;
    QPushButton *AddFriendButton;
    QPushButton *SignOutButton;
    QPushButton *FriendRequests;
    QLabel *labelRankName;
    QLabel *Img;
    QLabel *Img2;
    QLabel *Img3;
    QFrame *frame_2;
    QPushButton *AddTaskButton;
    QLabel *Categorylabel;
    QPushButton *CategoriesButton;
    QListWidget *ToDo;
    QListWidget *InProgress;
    QListWidget *Done;
    QLabel *ToDolabel;
    QLabel *InProgresslabel;
    QLabel *Donelabel;
    QPushButton *SearchOk;
    QLineEdit *SearchDepth;
    QLabel *SearchLabel;

    void setupUi(QMainWindow *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(1049, 645);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Form->setWindowIcon(icon);
        Form->setStyleSheet(QString::fromUtf8("QPushButton { border: 1px solid black }\n"
"QPushButton :hover { border: 1px solid green }\n"
"\n"
""));
        centralwidget = new QWidget(Form);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 261, 651));
        frame->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"   border: 1px solid black;\n"
"   border-left: none;\n"
"}\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        Friendlist = new QListWidget(frame);
        Friendlist->setObjectName(QString::fromUtf8("Friendlist"));
        Friendlist->setGeometry(QRect(30, 440, 201, 201));
        QFont font;
        font.setPointSize(11);
        Friendlist->setFont(font);
        Friendlist->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        Friendlist->setStyleSheet(QString::fromUtf8("QListWidget\n"
"{\n"
"	border: none;\n"
"}"));
        Friendlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        friendlabel = new QLabel(frame);
        friendlabel->setObjectName(QString::fromUtf8("friendlabel"));
        friendlabel->setGeometry(QRect(60, 400, 141, 31));
        QFont font1;
        font1.setPointSize(16);
        friendlabel->setFont(font1);
        friendlabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        labelName = new QLabel(frame);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(30, 30, 151, 31));
        labelName->setFont(font1);
        labelName->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        RankImg = new QLabel(frame);
        RankImg->setObjectName(QString::fromUtf8("RankImg"));
        RankImg->setGeometry(QRect(196, 28, 40, 40));
        RankImg->setFont(font1);
        RankImg->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        RankImg->setPixmap(QPixmap(QString::fromUtf8(":/Img/Ranks/immortal.png")));
        RankImg->setScaledContents(true);
        labelPoints = new QLabel(frame);
        labelPoints->setObjectName(QString::fromUtf8("labelPoints"));
        labelPoints->setGeometry(QRect(185, 80, 71, 16));
        labelPoints->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        ArchiveButton = new QPushButton(frame);
        ArchiveButton->setObjectName(QString::fromUtf8("ArchiveButton"));
        ArchiveButton->setGeometry(QRect(70, 220, 101, 41));
        ArchiveButton->setCursor(QCursor(Qt::PointingHandCursor));
        ArchiveButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"   border: 1px solid black;\n"
"}\n"
""));
        AddFriendButton = new QPushButton(frame);
        AddFriendButton->setObjectName(QString::fromUtf8("AddFriendButton"));
        AddFriendButton->setGeometry(QRect(70, 340, 101, 41));
        AddFriendButton->setCursor(QCursor(Qt::PointingHandCursor));
        SignOutButton = new QPushButton(frame);
        SignOutButton->setObjectName(QString::fromUtf8("SignOutButton"));
        SignOutButton->setGeometry(QRect(70, 160, 101, 41));
        SignOutButton->setCursor(QCursor(Qt::PointingHandCursor));
        FriendRequests = new QPushButton(frame);
        FriendRequests->setObjectName(QString::fromUtf8("FriendRequests"));
        FriendRequests->setGeometry(QRect(70, 280, 101, 41));
        FriendRequests->setCursor(QCursor(Qt::PointingHandCursor));
        FriendRequests->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"   border: 1px solid black;\n"
"}\n"
""));
        labelRankName = new QLabel(frame);
        labelRankName->setObjectName(QString::fromUtf8("labelRankName"));
        labelRankName->setGeometry(QRect(30, 80, 91, 16));
        labelRankName->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        Img = new QLabel(centralwidget);
        Img->setObjectName(QString::fromUtf8("Img"));
        Img->setGeometry(QRect(260, 0, 265, 651));
        Img->setAutoFillBackground(false);
        Img->setPixmap(QPixmap(QString::fromUtf8(":/Img/Img/LogoJpeg.jpg")));
        Img->setScaledContents(true);
        Img2 = new QLabel(centralwidget);
        Img2->setObjectName(QString::fromUtf8("Img2"));
        Img2->setGeometry(QRect(525, 0, 265, 651));
        Img2->setAutoFillBackground(true);
        Img2->setPixmap(QPixmap(QString::fromUtf8(":/Img/Img/LogoJpeg2.jpg")));
        Img2->setScaledContents(true);
        Img3 = new QLabel(centralwidget);
        Img3->setObjectName(QString::fromUtf8("Img3"));
        Img3->setGeometry(QRect(790, 0, 265, 651));
        Img3->setCursor(QCursor(Qt::PointingHandCursor));
        Img3->setAutoFillBackground(true);
        Img3->setPixmap(QPixmap(QString::fromUtf8(":/Img/Img/LogoJpeg.jpg")));
        Img3->setScaledContents(true);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(297, 20, 721, 611));
        frame_2->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color: white;\n"
"    border: 1px solid black;\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        AddTaskButton = new QPushButton(frame_2);
        AddTaskButton->setObjectName(QString::fromUtf8("AddTaskButton"));
        AddTaskButton->setGeometry(QRect(20, 20, 91, 41));
        AddTaskButton->setCursor(QCursor(Qt::PointingHandCursor));
        AddTaskButton->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid darkgreen;}"));
        Categorylabel = new QLabel(frame_2);
        Categorylabel->setObjectName(QString::fromUtf8("Categorylabel"));
        Categorylabel->setGeometry(QRect(248, 20, 221, 41));
        Categorylabel->setFont(font1);
        Categorylabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        CategoriesButton = new QPushButton(frame_2);
        CategoriesButton->setObjectName(QString::fromUtf8("CategoriesButton"));
        CategoriesButton->setGeometry(QRect(150, 20, 91, 41));
        CategoriesButton->setCursor(QCursor(Qt::PointingHandCursor));
        CategoriesButton->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid darkgreen;}"));
        ToDo = new QListWidget(frame_2);
        ToDo->setObjectName(QString::fromUtf8("ToDo"));
        ToDo->setGeometry(QRect(20, 100, 224, 491));
        ToDo->setFont(font);
        ToDo->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        ToDo->setStyleSheet(QString::fromUtf8(""));
        ToDo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        InProgress = new QListWidget(frame_2);
        InProgress->setObjectName(QString::fromUtf8("InProgress"));
        InProgress->setGeometry(QRect(243, 100, 234, 491));
        InProgress->setFont(font);
        InProgress->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        InProgress->setStyleSheet(QString::fromUtf8(""));
        InProgress->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        InProgress->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Done = new QListWidget(frame_2);
        Done->setObjectName(QString::fromUtf8("Done"));
        Done->setGeometry(QRect(476, 100, 224, 491));
        Done->setFont(font);
        Done->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        Done->setStyleSheet(QString::fromUtf8(""));
        Done->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ToDolabel = new QLabel(frame_2);
        ToDolabel->setObjectName(QString::fromUtf8("ToDolabel"));
        ToDolabel->setGeometry(QRect(67, 80, 131, 16));
        ToDolabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        InProgresslabel = new QLabel(frame_2);
        InProgresslabel->setObjectName(QString::fromUtf8("InProgresslabel"));
        InProgresslabel->setGeometry(QRect(320, 80, 81, 16));
        InProgresslabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        Donelabel = new QLabel(frame_2);
        Donelabel->setObjectName(QString::fromUtf8("Donelabel"));
        Donelabel->setGeometry(QRect(546, 80, 111, 16));
        Donelabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        SearchOk = new QPushButton(frame_2);
        SearchOk->setObjectName(QString::fromUtf8("SearchOk"));
        SearchOk->setGeometry(QRect(630, 20, 71, 41));
        SearchOk->setCursor(QCursor(Qt::PointingHandCursor));
        SearchOk->setStyleSheet(QString::fromUtf8("QPushButton {border: 1px solid black; } \n"
"QPushButton:hover { border: 1px solid darkgreen;}"));
        SearchDepth = new QLineEdit(frame_2);
        SearchDepth->setObjectName(QString::fromUtf8("SearchDepth"));
        SearchDepth->setGeometry(QRect(545, 20, 31, 41));
        SearchDepth->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QLineEdit\n"
"{\n"
"border:   1px solid black;\n"
"border-top:none;\n"
"border-right:none;\n"
"border-left:none;\n"
"padding-top:2px;\n"
"}"));
        SearchLabel = new QLabel(frame_2);
        SearchLabel->setObjectName(QString::fromUtf8("SearchLabel"));
        SearchLabel->setGeometry(QRect(480, 30, 151, 21));
        SearchLabel->setFont(font1);
        SearchLabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        SearchLabel->raise();
        AddTaskButton->raise();
        Categorylabel->raise();
        CategoriesButton->raise();
        ToDo->raise();
        InProgress->raise();
        Done->raise();
        ToDolabel->raise();
        InProgresslabel->raise();
        Donelabel->raise();
        SearchOk->raise();
        SearchDepth->raise();
        Form->setCentralWidget(centralwidget);
        Img->raise();
        Img3->raise();
        Img2->raise();
        frame->raise();
        frame_2->raise();

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QMainWindow *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "ToDoList", nullptr));
        friendlabel->setText(QCoreApplication::translate("Form", "       Friends", nullptr));
        labelName->setText(QCoreApplication::translate("Form", "Name Surname", nullptr));
        RankImg->setText(QString());
        labelPoints->setText(QCoreApplication::translate("Form", "Points: 150 rr", nullptr));
        ArchiveButton->setText(QCoreApplication::translate("Form", "History", nullptr));
        AddFriendButton->setText(QCoreApplication::translate("Form", "Add friend", nullptr));
        SignOutButton->setText(QCoreApplication::translate("Form", "Sign out", nullptr));
        FriendRequests->setText(QCoreApplication::translate("Form", "Friend requests", nullptr));
        labelRankName->setText(QCoreApplication::translate("Form", "Rank: Immortal", nullptr));
        Img->setText(QString());
        Img2->setText(QString());
        Img3->setText(QString());
        AddTaskButton->setText(QCoreApplication::translate("Form", "Add task", nullptr));
        Categorylabel->setText(QCoreApplication::translate("Form", "All Categories", nullptr));
        CategoriesButton->setText(QCoreApplication::translate("Form", "Categories", nullptr));
        ToDolabel->setText(QCoreApplication::translate("Form", "               TODO", nullptr));
        InProgresslabel->setText(QCoreApplication::translate("Form", " IN PROGRESS", nullptr));
        Donelabel->setText(QCoreApplication::translate("Form", "         DONE", nullptr));
        SearchOk->setText(QCoreApplication::translate("Form", "Ok", nullptr));
        SearchLabel->setText(QCoreApplication::translate("Form", "    Last      h", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
