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
                    //case for not arrays
                }

                //If data is array
                QJsonArray array = doc.array();
                vector<QJsonObject> Tasks;
                for(const auto &v : array)
                {
                    QJsonObject obj = v.toObject();
                    Tasks.emplace_back(obj);
                }
                for(const auto &x : Tasks)
                {
                    qDebug() << x.value("task_Header").toString() << " ";
                    //QListWidgetItem *item = new QListWidgetItem(x.value("task_Header").toString(), x.value("task_Start_Time").toString());
                    //ui->ToDo->addItem(x.value("task_Header").toString());

                    QString stringresult = x.value("task_Header").toString() + "\n" + x.value("task_Body").toString();


                    //Need to put it in separate class later
                    QListWidgetItem *newItem = new QListWidgetItem;
                    newItem->setText(stringresult);
                    newItem->setIcon(QIcon(":/Img/Img/test1day.png"));
                    ui->ToDo->addItem(newItem);
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







