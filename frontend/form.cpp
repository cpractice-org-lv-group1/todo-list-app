#include "form.h"
#include "ui_form.h"
using namespace std;

Form::Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    //UI STYLES
    this->setStyleSheet("background-color: white;");
    ui->AddFriendButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->ArchiveButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->SignOutButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid red;}");
    ui->ToDo->setIconSize(QSize(70, 70));
    ui->InProgress->setIconSize(QSize(70, 70));
    ui->Done->setIconSize(QSize(70, 70));
}

Form::~Form()
{
    delete ui;
}

void Form::on_SignOutButton_clicked()
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
                    //CASE FOR NOT ARRAYS
                }

                //IF DATA IS ARRAY
                QJsonArray array = doc.array();
                vector<QJsonObject> Tasks;
                for(const auto &v : array)
                {
                    QJsonObject obj = v.toObject();
                    Tasks.emplace_back(obj);
                }

                ListWidgetHelper::FillWithTasks(ui->ToDo, ui->InProgress, ui->Done, Tasks);

            }
            else
            {
                qDebug() << "Parse error: " << docError.errorString();
                return;
            }
        }
    }
}







