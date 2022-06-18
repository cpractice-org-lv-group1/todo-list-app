#include "form.h"
#include "ui_form.h"
using namespace std;

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

    Operations::GetTasks(id, socket);
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
            doc  = QJsonDocument::fromJson(Data, &docError);
            if(docError.errorString().toInt() == QJsonParseError::NoError)
            {
                if (!doc.isArray())
                {
                    qDebug() << "Document does not contain array";
                   // return;
                }

                //If everything is good
                QJsonArray array = doc.array();
                vector<QJsonObject> Tasks;
                for(const auto &v : array)
                {
                    QJsonObject obj = v.toObject();
                    Tasks.emplace_back(obj);
                }
                for(const auto &x : Tasks)
                {
                    qDebug() << x.value("task_Header") << " ";
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




