/********************************************************************************
** Form generated from reading UI file 'friendinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDINFO_H
#define UI_FRIENDINFO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendInfo
{
public:
    QWidget *centralwidget;
    QLabel *NameSurname;
    QLabel *RankIcon;
    QLabel *RankName;
    QLabel *Points;
    QLabel *Birthday;
    QLabel *Email;
    QLabel *FriendsSince;
    QPushButton *Reject;
    QPushButton *Accept;
    QPushButton *Delete;

    void setupUi(QMainWindow *FriendInfo)
    {
        if (FriendInfo->objectName().isEmpty())
            FriendInfo->setObjectName(QString::fromUtf8("FriendInfo"));
        FriendInfo->resize(267, 215);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        FriendInfo->setWindowIcon(icon);
        centralwidget = new QWidget(FriendInfo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NameSurname = new QLabel(centralwidget);
        NameSurname->setObjectName(QString::fromUtf8("NameSurname"));
        NameSurname->setGeometry(QRect(13, 0, 171, 51));
        QFont font;
        font.setPointSize(16);
        NameSurname->setFont(font);
        RankIcon = new QLabel(centralwidget);
        RankIcon->setObjectName(QString::fromUtf8("RankIcon"));
        RankIcon->setGeometry(QRect(204, 8, 40, 40));
        RankIcon->setScaledContents(true);
        RankName = new QLabel(centralwidget);
        RankName->setObjectName(QString::fromUtf8("RankName"));
        RankName->setGeometry(QRect(10, 50, 161, 16));
        Points = new QLabel(centralwidget);
        Points->setObjectName(QString::fromUtf8("Points"));
        Points->setGeometry(QRect(193, 50, 71, 16));
        Birthday = new QLabel(centralwidget);
        Birthday->setObjectName(QString::fromUtf8("Birthday"));
        Birthday->setGeometry(QRect(10, 110, 251, 16));
        Email = new QLabel(centralwidget);
        Email->setObjectName(QString::fromUtf8("Email"));
        Email->setGeometry(QRect(10, 80, 241, 16));
        FriendsSince = new QLabel(centralwidget);
        FriendsSince->setObjectName(QString::fromUtf8("FriendsSince"));
        FriendsSince->setGeometry(QRect(10, 140, 251, 16));
        Reject = new QPushButton(centralwidget);
        Reject->setObjectName(QString::fromUtf8("Reject"));
        Reject->setGeometry(QRect(10, 140, 101, 41));
        Reject->setCursor(QCursor(Qt::PointingHandCursor));
        Accept = new QPushButton(centralwidget);
        Accept->setObjectName(QString::fromUtf8("Accept"));
        Accept->setGeometry(QRect(150, 140, 101, 41));
        Accept->setCursor(QCursor(Qt::PointingHandCursor));
        Delete = new QPushButton(centralwidget);
        Delete->setObjectName(QString::fromUtf8("Delete"));
        Delete->setGeometry(QRect(80, 165, 101, 41));
        Delete->setCursor(QCursor(Qt::PointingHandCursor));
        FriendInfo->setCentralWidget(centralwidget);

        retranslateUi(FriendInfo);

        QMetaObject::connectSlotsByName(FriendInfo);
    } // setupUi

    void retranslateUi(QMainWindow *FriendInfo)
    {
        FriendInfo->setWindowTitle(QCoreApplication::translate("FriendInfo", "Friend Info", nullptr));
        NameSurname->setText(QCoreApplication::translate("FriendInfo", "Name + Surname", nullptr));
        RankIcon->setText(QCoreApplication::translate("FriendInfo", "rank", nullptr));
        RankName->setText(QCoreApplication::translate("FriendInfo", "Rank: ", nullptr));
        Points->setText(QCoreApplication::translate("FriendInfo", "Points:", nullptr));
        Birthday->setText(QCoreApplication::translate("FriendInfo", "Birthday:", nullptr));
        Email->setText(QCoreApplication::translate("FriendInfo", "Email:", nullptr));
        FriendsSince->setText(QCoreApplication::translate("FriendInfo", "Friends since:", nullptr));
        Reject->setText(QCoreApplication::translate("FriendInfo", "Reject", nullptr));
        Accept->setText(QCoreApplication::translate("FriendInfo", "Accept", nullptr));
        Delete->setText(QCoreApplication::translate("FriendInfo", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendInfo: public Ui_FriendInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDINFO_H
