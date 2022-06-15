#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    ifOpen = false;
    emit backSignal();
}

void Form::slot(int id, QTcpSocket *sock)
{
    socket = sock;
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    ifOpen = true;

    ui->label->setText(QString::number(id));

    QJsonObject GetById
    {
        {"Operation", "GetTasks"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
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

void Form::sockDisc()
{
    socket->deleteLater();
}

void Form::sockReady()
{
    if(ifOpen)
    {
        if (socket->waitForConnected(500))
        {
            socket->waitForReadyRead(500);
            Data = socket->readAll();
            qDebug() << Data;
        }
    }
}




