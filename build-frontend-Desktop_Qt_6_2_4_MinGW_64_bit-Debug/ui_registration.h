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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QWidget *centralwidget;
    QTextEdit *LogEmail;
    QTextEdit *LogPass;
    QLabel *LogIn_label;
    QPushButton *LoginButton;
    QLabel *Img;
    QLabel *LogEmail_label;
    QLabel *LogPass_label;
    QLabel *NeedAcc_label;
    QPushButton *GoToSign;
    QTextEdit *SignUpName;
    QTextEdit *SignUpSurname;
    QTextEdit *SignUpPass;
    QTextEdit *SignUpEmail;
    QTextEdit *SignUpPass2;
    QLabel *SignUp_label;
    QDateEdit *SignUpBirth;
    QPushButton *GoToLog;
    QLabel *HaveAcc_label;
    QPushButton *SignUpButton;
    QLabel *SignUpName_label;
    QLabel *SignUpSurname_label;
    QLabel *SignUpBirthday_label;
    QLabel *SignUpPass_label;
    QLabel *SignUpPass2_label;
    QLabel *SignUpEmail_label;
    QPushButton *SignUpBackButton;

    void setupUi(QMainWindow *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->setEnabled(true);
        Registration->resize(807, 503);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Registration->setWindowIcon(icon);
        Registration->setWindowOpacity(1.000000000000000);
        Registration->setStyleSheet(QString::fromUtf8("QPushButton { border: 1px solid black }\n"
"QPushButton :hover { border: 1px solid green }\n"
"QTextEdit { border: 1px solid black }\n"
""));
        centralwidget = new QWidget(Registration);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LogEmail = new QTextEdit(centralwidget);
        LogEmail->setObjectName(QString::fromUtf8("LogEmail"));
        LogEmail->setGeometry(QRect(500, 200, 231, 41));
        QFont font;
        font.setPointSize(14);
        LogEmail->setFont(font);
        LogPass = new QTextEdit(centralwidget);
        LogPass->setObjectName(QString::fromUtf8("LogPass"));
        LogPass->setGeometry(QRect(500, 280, 231, 41));
        LogPass->setFont(font);
        LogIn_label = new QLabel(centralwidget);
        LogIn_label->setObjectName(QString::fromUtf8("LogIn_label"));
        LogIn_label->setGeometry(QRect(570, 90, 101, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(22);
        LogIn_label->setFont(font1);
        LoginButton = new QPushButton(centralwidget);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(570, 350, 101, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        LoginButton->setFont(font2);
        LoginButton->setCursor(QCursor(Qt::PointingHandCursor));
        Img = new QLabel(centralwidget);
        Img->setObjectName(QString::fromUtf8("Img"));
        Img->setGeometry(QRect(0, 0, 421, 511));
        Img->setPixmap(QPixmap(QString::fromUtf8(":/Img/Img/LogoJpeg.jpg")));
        Img->setScaledContents(true);
        LogEmail_label = new QLabel(centralwidget);
        LogEmail_label->setObjectName(QString::fromUtf8("LogEmail_label"));
        LogEmail_label->setGeometry(QRect(500, 180, 49, 16));
        LogEmail_label->setFont(font2);
        LogPass_label = new QLabel(centralwidget);
        LogPass_label->setObjectName(QString::fromUtf8("LogPass_label"));
        LogPass_label->setGeometry(QRect(500, 260, 49, 16));
        LogPass_label->setFont(font2);
        NeedAcc_label = new QLabel(centralwidget);
        NeedAcc_label->setObjectName(QString::fromUtf8("NeedAcc_label"));
        NeedAcc_label->setGeometry(QRect(535, 424, 101, 16));
        GoToSign = new QPushButton(centralwidget);
        GoToSign->setObjectName(QString::fromUtf8("GoToSign"));
        GoToSign->setGeometry(QRect(620, 420, 80, 24));
        QFont font3;
        font3.setUnderline(true);
        GoToSign->setFont(font3);
        GoToSign->setCursor(QCursor(Qt::PointingHandCursor));
        SignUpName = new QTextEdit(centralwidget);
        SignUpName->setObjectName(QString::fromUtf8("SignUpName"));
        SignUpName->setGeometry(QRect(100, 120, 231, 41));
        SignUpSurname = new QTextEdit(centralwidget);
        SignUpSurname->setObjectName(QString::fromUtf8("SignUpSurname"));
        SignUpSurname->setGeometry(QRect(100, 200, 231, 41));
        SignUpPass = new QTextEdit(centralwidget);
        SignUpPass->setObjectName(QString::fromUtf8("SignUpPass"));
        SignUpPass->setGeometry(QRect(100, 200, 231, 41));
        SignUpEmail = new QTextEdit(centralwidget);
        SignUpEmail->setObjectName(QString::fromUtf8("SignUpEmail"));
        SignUpEmail->setGeometry(QRect(100, 120, 231, 41));
        SignUpPass2 = new QTextEdit(centralwidget);
        SignUpPass2->setObjectName(QString::fromUtf8("SignUpPass2"));
        SignUpPass2->setGeometry(QRect(100, 280, 231, 41));
        SignUp_label = new QLabel(centralwidget);
        SignUp_label->setObjectName(QString::fromUtf8("SignUp_label"));
        SignUp_label->setGeometry(QRect(150, 30, 121, 61));
        SignUp_label->setFont(font1);
        SignUpBirth = new QDateEdit(centralwidget);
        SignUpBirth->setObjectName(QString::fromUtf8("SignUpBirth"));
        SignUpBirth->setGeometry(QRect(100, 280, 231, 41));
        SignUpBirth->setStyleSheet(QString::fromUtf8("QDateEdit\n"
"{\n"
"    background-color: white;\n"
"    border: 1px solid black;\n"
"    spacing: 0 px; \n"
"    padding-left: 80px;\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"    width:50px;\n"
"    height:15px;\n"
"    subcontrol-position: right top;\n"
"    subcontrol-origin:margin;\n"
"    background-color: white;\n"
"    border: 1px solid black;\n"
"   spacing: 0 px; \n"
"}"));
        SignUpBirth->setFrame(true);
        SignUpBirth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        SignUpBirth->setProperty("showGroupSeparator", QVariant(true));
        GoToLog = new QPushButton(centralwidget);
        GoToLog->setObjectName(QString::fromUtf8("GoToLog"));
        GoToLog->setGeometry(QRect(210, 420, 80, 24));
        GoToLog->setFont(font3);
        GoToLog->setCursor(QCursor(Qt::PointingHandCursor));
        HaveAcc_label = new QLabel(centralwidget);
        HaveAcc_label->setObjectName(QString::fromUtf8("HaveAcc_label"));
        HaveAcc_label->setGeometry(QRect(120, 424, 101, 16));
        SignUpButton = new QPushButton(centralwidget);
        SignUpButton->setObjectName(QString::fromUtf8("SignUpButton"));
        SignUpButton->setGeometry(QRect(160, 350, 101, 41));
        SignUpButton->setCursor(QCursor(Qt::PointingHandCursor));
        SignUpName_label = new QLabel(centralwidget);
        SignUpName_label->setObjectName(QString::fromUtf8("SignUpName_label"));
        SignUpName_label->setGeometry(QRect(100, 100, 49, 16));
        SignUpSurname_label = new QLabel(centralwidget);
        SignUpSurname_label->setObjectName(QString::fromUtf8("SignUpSurname_label"));
        SignUpSurname_label->setGeometry(QRect(100, 180, 49, 16));
        SignUpBirthday_label = new QLabel(centralwidget);
        SignUpBirthday_label->setObjectName(QString::fromUtf8("SignUpBirthday_label"));
        SignUpBirthday_label->setGeometry(QRect(100, 260, 49, 16));
        SignUpPass_label = new QLabel(centralwidget);
        SignUpPass_label->setObjectName(QString::fromUtf8("SignUpPass_label"));
        SignUpPass_label->setGeometry(QRect(100, 180, 49, 16));
        SignUpPass2_label = new QLabel(centralwidget);
        SignUpPass2_label->setObjectName(QString::fromUtf8("SignUpPass2_label"));
        SignUpPass2_label->setGeometry(QRect(100, 260, 91, 16));
        SignUpEmail_label = new QLabel(centralwidget);
        SignUpEmail_label->setObjectName(QString::fromUtf8("SignUpEmail_label"));
        SignUpEmail_label->setGeometry(QRect(100, 100, 49, 16));
        SignUpBackButton = new QPushButton(centralwidget);
        SignUpBackButton->setObjectName(QString::fromUtf8("SignUpBackButton"));
        SignUpBackButton->setGeometry(QRect(100, 350, 101, 41));
        SignUpBackButton->setCursor(QCursor(Qt::PointingHandCursor));
        Registration->setCentralWidget(centralwidget);
        Img->raise();
        LogEmail->raise();
        LogPass->raise();
        LogIn_label->raise();
        LoginButton->raise();
        LogEmail_label->raise();
        LogPass_label->raise();
        NeedAcc_label->raise();
        GoToSign->raise();
        SignUpName->raise();
        SignUpSurname->raise();
        SignUpPass->raise();
        SignUpEmail->raise();
        SignUpPass2->raise();
        SignUp_label->raise();
        SignUpBirth->raise();
        GoToLog->raise();
        HaveAcc_label->raise();
        SignUpButton->raise();
        SignUpName_label->raise();
        SignUpSurname_label->raise();
        SignUpBirthday_label->raise();
        SignUpPass_label->raise();
        SignUpPass2_label->raise();
        SignUpEmail_label->raise();
        SignUpBackButton->raise();

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QMainWindow *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "ToDoList", nullptr));
        LogIn_label->setText(QCoreApplication::translate("Registration", "Log In", nullptr));
        LoginButton->setText(QCoreApplication::translate("Registration", "Login", nullptr));
        Img->setText(QString());
        LogEmail_label->setText(QCoreApplication::translate("Registration", "Email", nullptr));
        LogPass_label->setText(QCoreApplication::translate("Registration", "Password", nullptr));
        NeedAcc_label->setText(QCoreApplication::translate("Registration", "Need an account?", nullptr));
        GoToSign->setText(QCoreApplication::translate("Registration", "SIGN UP", nullptr));
        SignUp_label->setText(QCoreApplication::translate("Registration", "  Sign Up", nullptr));
        GoToLog->setText(QCoreApplication::translate("Registration", "LOG IN", nullptr));
        HaveAcc_label->setText(QCoreApplication::translate("Registration", "Have an account?", nullptr));
        SignUpButton->setText(QCoreApplication::translate("Registration", "Next", nullptr));
        SignUpName_label->setText(QCoreApplication::translate("Registration", "Name", nullptr));
        SignUpSurname_label->setText(QCoreApplication::translate("Registration", "Surname", nullptr));
        SignUpBirthday_label->setText(QCoreApplication::translate("Registration", "Birthday", nullptr));
        SignUpPass_label->setText(QCoreApplication::translate("Registration", "Password", nullptr));
        SignUpPass2_label->setText(QCoreApplication::translate("Registration", "Repeat password", nullptr));
        SignUpEmail_label->setText(QCoreApplication::translate("Registration", "Email", nullptr));
        SignUpBackButton->setText(QCoreApplication::translate("Registration", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
