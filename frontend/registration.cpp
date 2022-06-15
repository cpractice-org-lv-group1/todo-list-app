#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);

    form = new Form ();
    connect(this, &Registration::mySignal, form, &Form::slot);
    connect(form, SIGNAL(backSignal()), this, SLOT(ChangeWin()));

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    socket->connectToHost("127.0.0.1", 8888);

    ifOpen = true;

    //UI Styles
    ui->LoginButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->LogEmail->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
    ui->LogPass->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
    ui->GoToSign->setStyleSheet("QPushButton {border: none;color: palette(window-text);background: transparent;} QPushButton:hover { color:darkgreen;}");
    ui->GoToLog->setStyleSheet("QPushButton {border: none;color: palette(window-text);background: transparent;} QPushButton:hover { color:darkgreen;}");
    ui->LoginButton->setFocusPolicy(Qt::NoFocus);
    this->setStyleSheet("background-color: white;");
    font.setPointSize(14);

    //On Load
    connect(this, &Registration::ShowLogIn, this, &Registration::ShowLogInSlot);
    connect(this, &Registration::ShowSignUp, this, &Registration::ShowSignUpSlot);
    emit ShowLogIn();
}

Registration::~Registration()
{
    delete ui;
    delete form;
}


void Registration::on_LoginButton_clicked()
{
    QJsonObject User
    {
        {"Operation", "Login"},
        {"Email", ui->LogEmail->toPlainText()},
        {"Password", ui->LogPass->toPlainText()},
    };

    QJsonArray jsarray {User};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }

    qDebug() << formatted;
}

void Registration::ChangeWin()
{
    this->show();
    form->hide();
    ifOpen = true;
}

void Registration::sockDisc()
{
    socket->deleteLater();
}

void Registration::sockReady()
{
    if(ifOpen)
    {
        if (socket->waitForConnected(500))
        {
            socket->waitForReadyRead(500);
            Data = socket->readAll();
            QString sData(Data);
            Id = sData.toInt();
            qDebug() << Id;
        }
        this->hide();
        form->show();
        ifOpen = false;
        emit mySignal(Id, socket);
    }
}

void Registration::on_GoToSign_clicked()
{
    emit ShowSignUp();
    ui->Img->move(400,0);
}


void Registration::on_GoToLog_clicked()
{
    emit ShowLogIn();
    ui->Img->move(0,0);
    ui->SignUpButton->move(160,350);
}

void Registration::ShowLogInSlot()
{
    ui->SignUp_label->hide();
    ui->SignUpName->hide();
    ui->SignUpName_label->hide();
    ui->SignUpSurname->hide();
    ui->SignUpSurname_label->hide();
    ui->SignUpBirth->hide();
    ui->SignUpBirthday_label->hide();
    ui->SignUpPass->hide();
    ui->SignUpPass_label->hide();
    ui->SignUpPass2->hide();
    ui->SignUpPass2_label->hide();
    ui->SignUpEmail->hide();
    ui->SignUpEmail_label->hide();
    ui->GoToLog->hide();
    ui->HaveAcc_label->hide();
    ui->SignUpButton->hide();
    ui->SignUpBackButton->hide();

    ui->LogIn_label->show();
    ui->LogEmail->show();
    ui->LogEmail_label->show();
    ui->LogPass->show();
    ui->LogPass_label->show();
    ui->LoginButton->show();
    ui->NeedAcc_label->show();
    ui->GoToSign->show();
}

void Registration::ShowSignUpSlot()
{
    ui->SignUp_label->show();
    ui->SignUpName->show();
    ui->SignUpName->setStyleSheet("border: 1px solid black");
    ui->SignUpName->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
    ui->SignUpName->setFont(font);
    ui->SignUpName_label->show();
    ui->SignUpSurname->show();
    ui->SignUpSurname->setStyleSheet("border: 1px solid black");
    ui->SignUpSurname->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
    ui->SignUpSurname->setFont(font);
    ui->SignUpSurname_label->show();
    ui->SignUpBirth->show();
    ui->SignUpBirth->setStyleSheet("border: 1px solid black");
    ui->SignUpBirth->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
    ui->SignUpBirth->setFont(font);
    ui->SignUpBirthday_label->show();
    ui->GoToLog->show();
    ui->HaveAcc_label->show();
    ui->SignUpButton->show();
    ui->SignUpButton->setStyleSheet("border: 1px solid black");
    ui->SignUpButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->SignUpBirth->setStyleSheet("QDateEdit{background-color: white;border: 1px solid black;spacing: 0 px; padding-left: 70px; padding-bottom:3px;}QDateEdit:focus { border: 1px solid darkgreen;}");


    ui->LogIn_label->hide();
    ui->LogEmail->hide();
    ui->LogEmail_label->hide();
    ui->LogPass->hide();
    ui->LogPass_label->hide();
    ui->LoginButton->hide();
    ui->NeedAcc_label->hide();
    ui->GoToSign->hide();

    ui->SignUpButton->setText("Next");
}

//when user filled name, surname and birthday
void Registration::on_SignUpButton_clicked()
{
    //case if fields are good
    if(ui->SignUpButton->text() == "Next")
    {
        ui->SignUpPass->show();
        ui->SignUpPass->setStyleSheet("border: 1px solid black");
        ui->SignUpPass->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
        ui->SignUpPass->setFont(font);
        ui->SignUpPass_label->show();
        ui->SignUpPass2->show();
        ui->SignUpPass2->setStyleSheet("border: 1px solid black");
        ui->SignUpPass2->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
        ui->SignUpPass2->setFont(font);
        ui->SignUpPass2_label->show();
        ui->SignUpEmail->show();
        ui->SignUpEmail->setStyleSheet("border: 1px solid black");
        ui->SignUpEmail->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
        ui->SignUpEmail->setFont(font);
        ui->SignUpEmail_label->show();
        ui->SignUpBackButton->show();
        ui->SignUpBackButton->setStyleSheet("border: 1px solid black");
        ui->SignUpBackButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
        ui->SignUpButton->move(230,350);

        ui->SignUpName->hide();
        ui->SignUpName_label->hide();
        ui->SignUpSurname->hide();
        ui->SignUpSurname_label->hide();
        ui->SignUpBirth->hide();
        ui->SignUpBirthday_label->hide();

        ui->SignUpButton->setText("Sign Up");
    }
    else if(ui->SignUpButton->text() == "Sign Up")
    {
         // check for sign up
    }
}

void Registration::on_SignUpBackButton_clicked()
{
    ui->SignUpPass->hide();
    ui->SignUpPass_label->hide();
    ui->SignUpPass2->hide();
    ui->SignUpPass2_label->hide();
    ui->SignUpEmail->hide();
    ui->SignUpEmail_label->hide();
    ui->SignUpBackButton->hide();
    ui->SignUpButton->move(160,350);

    ui->SignUpName->show();
    ui->SignUpName_label->show();
    ui->SignUpSurname->show();
    ui->SignUpSurname_label->show();
    ui->SignUpBirth->show();
    ui->SignUpBirthday_label->show();

    ui->SignUpButton->setText("Next");
}

