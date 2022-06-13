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
}

Registration::~Registration()
{
    delete ui;
    delete form;
}


void Registration::on_pushButton_clicked()
{
   this->hide();
    form->show();
    emit mySignal(ui->LogEmail->toPlainText());


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
}

void Registration::sockDisc()
{
    socket->deleteLater();
}

void Registration::sockReady()
{
    qDebug()<< "Connected";
    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug()<<Data;
    }
}

