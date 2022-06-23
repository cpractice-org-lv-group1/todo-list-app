#include "registration.h"
#include "ui_registration.h"

//CONSTRUCTOR
Registration::Registration(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);

    //INITIALIZATION OF SIGNALS AND KEY COMPONENTS
    form = new Form ();
    connect(this, &Registration::mySignal, form, &Form::slot);
    connect(form, SIGNAL(backSignal()), this, SLOT(ChangeWin()));
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    connect(this, &Registration::ShowLogIn, this, &Registration::ShowLogInSlot);
    connect(this, &Registration::ShowSignUp, this, &Registration::ShowSignUpSlot);
    socket->connectToHost("127.0.0.1", 8888);
    ifOpen = true;

    //UI STYLES
    ui->LoginButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->LogEmail->setStyleSheet("QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}");
    ui->LogPass->setStyleSheet("QLineEdit {border: 1px solid black; padding-bottom:3px;} QLineEdit:focus { border: 1px solid darkgreen;}");
    ui->GoToSign->setStyleSheet("QPushButton {border: none;color: palette(window-text);background: transparent;} QPushButton:hover { color:darkgreen;}");
    ui->GoToLog->setStyleSheet("QPushButton {border: none;color: palette(window-text);background: transparent;} QPushButton:hover { color:darkgreen;}");
    this->setStyleSheet("background-color: white;");
    font.setPointSize(14);
    ui->LogWrongEmail->setStyleSheet("color: red");
    ui->LogWrongPass->setStyleSheet("color: red");
    ui->LogPass->setEchoMode(QLineEdit::Password);
    this->setFixedSize(807,503);

    //SHOW LOGIN AS DEFAULT WINDOW
    emit ShowLogIn();

    //GET REMEMBERED DATA
    QFile file;
    file.setFileName("userdata.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QString email = stream.readLine();
    QString pass = stream.readLine();
    ui->LogEmail->setText(email);
    ui->LogPass->setText(pass);
    file.close();
}

//DESTRUCTOR
Registration::~Registration()
{
    delete ui;
    delete form;
}

//FUNCTION FOR CLICK ON LOGIN BUTTON
void Registration::on_LoginButton_clicked()
{
    //IF BOTH EMAIL AND PASSWORD IS NOT EMPTY SEND REQUEST TO SERVER
    if(!ui->LogEmail->document()->isEmpty() && !ui->LogPass->text().isEmpty())
    {
        ui->LogWrongEmail->hide();
        ui->LogWrongPass->hide();

        //FORM JSON DATA TO SEND
        QJsonObject User
        {
            {"Operation", "Login"},
            {"Email", ui->LogEmail->toPlainText()},
            {"Password", ui->LogPass->text()},
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
    //CASES FOR WHEN SOME OR BOTH FIELDS ARE EMPTY SO NO NEED TO SEND REQUEST
    else
    {
        if(ui->LogEmail->document()->isEmpty() && !ui->LogPass->text().isEmpty())
        {
            ui->LogWrongEmail->setStyleSheet("color: red");
            ui->LogWrongEmail->setText("             Enter email!");
            ui->LogWrongEmail->show();
            ui->LogWrongPass->hide();
        }
        else if(ui->LogPass->text().isEmpty() && !ui->LogEmail->document()->isEmpty())
        {
            ui->LogWrongPass->setText("   Enter password!");
            ui->LogWrongPass->show();
            ui->LogWrongEmail->hide();
        }
        else
        {
            ui->LogWrongEmail->setText("             Enter email!");
            ui->LogWrongPass->setText("   Enter password!");
            ui->LogWrongPass->show();
            ui->LogWrongEmail->show();
        }
    }

}

//FUNCTION TO GET BACK TO THIS WINDOW FROM MAIN WINDOW
void Registration::ChangeWin()
{
    this->show();
    form->hide();
    ifOpen = true;
}

//DESTRUCTOR OF SOCKET
void Registration::sockDisc()
{
    socket->deleteLater();
}

//HANDLER OF DATA FROM SERVER
void Registration::sockReady()
{
    if(ifOpen)
    {
        if (socket->waitForConnected(500))
        {
            socket->waitForReadyRead(500);
            Data = socket->readAll();
            qDebug() << Data;
            doc  = QJsonDocument::fromJson(Data, &docError);
            if(docError.errorString().toInt() == QJsonParseError::NoError)
            {
//------------------------------------------IF LOGIN--------------------------------------//
                if(doc.object().value("Operation").toString() == "Login")
                {
                    //LOGIN SUCCSESSFUL
                    if(doc.object().value("Result").toString() == "Success Login")
                    {
                        this->hide();
                        form->show();
                        ifOpen = false;
                        //Write remember me to file
                        if(ui->RememberMe->isChecked())
                        {
                            QFile file;
                            file.setFileName("userdata.txt");
                            file.open(QIODevice::WriteOnly);
                            QTextStream stream(&file);
                            stream << ui->LogEmail->toPlainText() + "\r\n";
                            stream << ui->LogPass->text() + "\r\n";
                            file.close();
                        }
                        else
                        {
                            QFile file;
                            file.setFileName("userdata.txt");
                            file.open(QIODevice::WriteOnly);
                            QTextStream stream(&file);
                            stream << "";
                            file.close();
                        }
                        //GO TO MAIN WINDOW
                        emit mySignal(doc.object().value("userID").toInt(), socket);
                    }
                    //WRONG EMAIL
                    else if(doc.object().value("Result").toString() == "Erorr Email")
                    {
                        ui->LogWrongPass->hide();
                        ui->LogWrongEmail->setStyleSheet("color: red");
                        ui->LogWrongEmail->setText("          Wrong email!");
                        ui->LogWrongEmail->show();
                        return;
                    }
                    //WRONG PASSWORD
                    else if(doc.object().value("Result").toString() == "Erorr Password")
                    {
                        ui->LogWrongEmail->hide();
                        ui->LogWrongPass->setText("Wrong password!");
                        ui->LogWrongPass->show();
                        return;
                    }
                    //WRONG RESULT VALUE
                    else
                    {
                        qDebug() << "Wrong Result value!";
                        return;
                    }
                }
//------------------------------------------IF SIGNUP--------------------------------------//
                else if(doc.object().value("Operation").toString() == "SignUp")
                {
                    //SIGNUP SUCCSESSFUL
                    if(doc.object().value("Result").toString() == "Success SignUp")
                    {
                        qDebug() << "Success signup!";
                        emit ShowLogIn();
                        ui->Img->move(0,0);
                        ui->SignUpButton->move(160,350);
                        ui->LogEmail->setText(ui->SignUpEmail->toPlainText());
                        ui->LogWrongEmail->show();
                        ui->LogWrongEmail->setStyleSheet("color: green");
                        ui->LogWrongEmail->setText(" Signup successful!");
                    }
                    //SIGNUP NOT SUCCSESSFUL
                    else if(doc.object().value("Result").toString() == "Erorr SignUp")
                    {
                        qDebug() << "Error signup!";
                        return;
                    }
                    //WRONG RESULT VALUE
                    else
                    {
                        qDebug() << "Wrong Result value!";
                        return;
                    }
                }
//-------------------------------------WRONG OPERATION--------------------------------------//
                else
                {
                    qDebug() << "Wrong Operation value!";
                    return;
                }

            }
            else
            {
                qDebug() << "Parse error: " << docError.errorString();
                return;
            }
        }

    }
}

//BUTTON TO GO TO SIGN UP
void Registration::on_GoToSign_clicked()
{
    emit ShowSignUp();
    ui->Img->move(400,0);
}

//BUTTON TO GO TO LOG IN
void Registration::on_GoToLog_clicked()
{
    emit ShowLogIn();
    ui->Img->move(0,0);
    ui->SignUpButton->move(160,350);
}

//--------------------------SLOT TO SHOW LOG IN--------------------------//
void Registration::ShowLogInSlot()
{
    //HIDE SIGNUP FIELDS
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
    //HIDE SIGNUP ERRORS
    ui->SignUpWrongName->hide();
    ui->SignUpWrongSur->hide();
    ui->SignUpWrongEmail->hide();
    ui->SignUpWrongPass->hide();
    ui->SignUpWrongPass2->hide();


    //SHOW LOGIN FIELDS
    ui->LogIn_label->show();
    ui->LogEmail->show();
    ui->LogEmail_label->show();
    ui->LogPass->show();
    ui->LogPass_label->show();
    ui->LoginButton->show();
    ui->NeedAcc_label->show();
    ui->GoToSign->show();
    ui->RememberMe->show();
    //HIDE LOGIN ERRORS
    ui->LogWrongEmail->hide();
    ui->LogWrongPass->hide();
}

//--------------------------SLOT TO SHOW SIGN UP--------------------------//
void Registration::ShowSignUpSlot()
{
    //SHOW SIGNUP FIELDS
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

    //HIDE LOGIN FIELDS
    ui->LogIn_label->hide();
    ui->LogEmail->hide();
    ui->LogEmail_label->hide();
    ui->LogPass->hide();
    ui->LogPass_label->hide();
    ui->LoginButton->hide();
    ui->NeedAcc_label->hide();
    ui->GoToSign->hide();
    ui->LogWrongEmail->hide();
    ui->LogWrongPass->hide();
    ui->RememberMe->hide();

    //SET VALUE OF NEXT/SIGNUP BUTTON
    ui->SignUpButton->setText("Next");
}

//----------------------------------NEXT/SIGNUP BUTTON----------------------------------//
void Registration::on_SignUpButton_clicked()
{
//---------------------------------FIRT HALF ON SIGN UP---------------------------------//
    if(ui->SignUpButton->text() == "Next")
    {
        //IF FIELDS ARE NOT EMPTY
        if(!ui->SignUpName->document()->isEmpty() && !ui->SignUpSurname->document()->isEmpty())
        {
            ui->SignUpWrongName->hide();
            ui->SignUpWrongSur->hide();

            //HIDE FIRST HALF
            ui->SignUpName->hide();
            ui->SignUpName_label->hide();
            ui->SignUpSurname->hide();
            ui->SignUpSurname_label->hide();
            ui->SignUpBirth->hide();
            ui->SignUpBirthday_label->hide();

            //SHOW SECOND HALF
            ui->SignUpPass->show();
            ui->SignUpPass->setStyleSheet("border: 1px solid black");
            ui->SignUpPass->setStyleSheet("QLineEdit {border: 1px solid black; padding-bottom:3px;} QLineEdit:focus { border: 1px solid darkgreen;}");
            ui->SignUpPass->setEchoMode(QLineEdit::Password);
            ui->SignUpPass->setFont(font);
            ui->SignUpPass_label->show();
            ui->SignUpPass2->show();
            ui->SignUpPass2->setStyleSheet("border: 1px solid black");
            ui->SignUpPass2->setStyleSheet("QLineEdit {border: 1px solid black; padding-bottom:3px;} QLineEdit:focus { border: 1px solid darkgreen;}");
            ui->SignUpPass2->setEchoMode(QLineEdit::Password);
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

            //SET VALUE OF NEXT/SIGNUP BUTTON
            ui->SignUpButton->setText("Sign Up");
        }
        //IF SOME FIELDS ARE EMPTY
        else
        {
            //IF NAME IS EMPTY
            if(ui->SignUpName->document()->isEmpty() && !ui->SignUpSurname->document()->isEmpty())
            {
                ui->SignUpWrongName->setStyleSheet("color: red");
                ui->SignUpWrongName->show();
                ui->SignUpWrongSur->hide();
            }
            //IF SURNAME IS EMPTY
            else if(!ui->SignUpName->document()->isEmpty() && ui->SignUpSurname->document()->isEmpty())
            {
                ui->SignUpWrongSur->setStyleSheet("color: red");
                ui->SignUpWrongSur->show();
                ui->SignUpWrongName->hide();
            }
            //IF BOTH ARE EMPTY
            else
            {
                ui->SignUpWrongSur->setStyleSheet("color: red");
                ui->SignUpWrongName->setStyleSheet("color: red");
                ui->SignUpWrongSur->show();
                ui->SignUpWrongName->show();
            }
        }
    }
//---------------------------------SECOND HALF ON SIGN UP---------------------------------//
    else if(ui->SignUpButton->text() == "Sign Up")
    {
        //VALUE TO SE STATE OF FIELDS
        bool ifEmail = false;
        bool ifPass = false;
        bool ifPass2 = false;

        //CHECK FOR EMPTY
        if(ui->SignUpEmail->document()->isEmpty())
        {
            ui->SignUpWrongEmail->setStyleSheet("color: red");
            ui->SignUpWrongEmail->setText("   Enter email!");
            ui->SignUpWrongEmail->show();
        }
        if(ui->SignUpPass->text().isEmpty())
        {
            ui->SignUpWrongPass->setStyleSheet("color: red");
            ui->SignUpWrongPass->setText("                             Enter password!");
            ui->SignUpWrongPass->show();
        }
        if(ui->SignUpPass2->text().isEmpty())
        {
            ui->SignUpWrongPass2->setStyleSheet("color: red");
            ui->SignUpWrongPass2->setText("                Repeat password!");
            ui->SignUpWrongPass2->show();
        }

        //REGEX CHECK FOR EMAIL
        if(!ui->SignUpEmail->document()->isEmpty())
        {
            const QRegularExpression regex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", QRegularExpression::CaseInsensitiveOption);
            if(regex.match(ui->SignUpEmail->document()->toPlainText()).hasMatch())
            {
                ui->SignUpWrongEmail->hide();
                ifEmail = true;
            }
            else
            {
                ui->SignUpWrongEmail->setStyleSheet("color: red");
                ui->SignUpWrongEmail->setText("Wrong email!");
                ui->SignUpWrongEmail->show();
                ifEmail = false;
            }
        }

        //CHECK FOR PASSWORD
        if(!ui->SignUpPass->text().isEmpty())
        {
            QString password = ui->SignUpPass->text();

            if(password.length() < 8)
            {
                ui->SignUpWrongPass->setStyleSheet("color: red");
                ui->SignUpWrongPass->setText("        You need at least 8 symbols!");
                ui->SignUpWrongPass->show();
                ifPass = false;
            }
            else
            {
                bool ifDigit = false;
                for (int i = 0; i<password.length(); i++)
                {
                    if (password[i].isDigit())
                    {
                        ifDigit = true;
                        break;
                    }
                }
                if(!ifDigit)
                {
                    ui->SignUpWrongPass->setStyleSheet("color: red");
                    ui->SignUpWrongPass->setText(" At least one number is required!");
                    ui->SignUpWrongPass->show();
                    ifPass = false;
                }
                else
                {
                    ifPass = true;
                }
            }
        }

        //CHECK FOR REPEAT PASSWORD
        if(!ui->SignUpPass2->text().isEmpty() && ifPass)
        {
            if(ui->SignUpPass->text() != ui->SignUpPass2->text())
            {
                ui->SignUpWrongPass2->setStyleSheet("color: red");
                ui->SignUpWrongPass2->setText("  Passwords should match!");
                ui->SignUpWrongPass2->show();
                ifPass2 = false;
            }
            else
            {
                ifPass2 = true;
            }
        }

        //IF PASS HAS ERRORS NO NEED TO SHOW PASS2 ERRORS
        if(!ui->SignUpPass2->text().isEmpty() && !ifPass)
        {
            ui->SignUpWrongPass2->hide();
        }

        //IF ANY IS OK
        if(ifEmail) ui->SignUpWrongEmail->hide();
        if(ifPass) ui->SignUpWrongPass->hide();
        if(ifPass2) ui->SignUpWrongPass2->hide();

        //IF EVERYTHING IS OK
        if(ifEmail && ifPass && ifPass2)
        {
            ui->SignUpWrongEmail->hide();
            ui->SignUpWrongPass->hide();
            ui->SignUpWrongPass2->hide();
//----------------------------------------PUT METHOD---------------------------------------//
            QJsonObject NewUser
            {
                {"Operation", "SignUp"},
                {"userNameArr", ui->SignUpName->toPlainText()},
                {"userSurnameArr", ui->SignUpSurname->toPlainText()},
                {"userBithday", ui->SignUpBirth->date().toString("yyyy-MM-dd")},
                {"userMail", ui->SignUpEmail->toPlainText()},
                {"userPassword", ui->SignUpPass->text()},
            };

            QJsonArray jsarray {NewUser};
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
    }
}

//BUTTON TO GO BACK FROM SIGN UP PART 2 TO PART 1
void Registration::on_SignUpBackButton_clicked()
{
    //HIDE PART 2
    ui->SignUpPass->hide();
    ui->SignUpPass_label->hide();
    ui->SignUpWrongPass->hide();
    ui->SignUpPass2->hide();
    ui->SignUpPass2_label->hide();
    ui->SignUpWrongPass2->hide();
    ui->SignUpEmail->hide();
    ui->SignUpEmail_label->hide();
    ui->SignUpWrongEmail->hide();
    ui->SignUpBackButton->hide();
    ui->SignUpButton->move(160,350);

    //SHOW PART 1
    ui->SignUpName->show();
    ui->SignUpName_label->show();
    ui->SignUpSurname->show();
    ui->SignUpSurname_label->show();
    ui->SignUpBirth->show();
    ui->SignUpBirthday_label->show();

    //SET VALUE OF NEXT/SIGNUP BUTTON
    ui->SignUpButton->setText("Next");
}

