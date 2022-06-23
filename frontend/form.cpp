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
    ui->FriendRequests->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->ToDo->setIconSize(QSize(70, 70));
    ui->InProgress->setIconSize(QSize(70, 70));
    ui->Done->setIconSize(QSize(70, 70));
    this->setFixedSize(1049,645);
    font.setPointSize(16);
    ui->SearchDepth->setFont(font);


    //SIGNALS
    taskwindow = new TaskInfo;
    connect(ui->ToDo, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onTaskClicked(QListWidgetItem*)));
    connect(ui->InProgress, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onTaskClicked(QListWidgetItem*)));
    connect(ui->Done, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onTaskClicked(QListWidgetItem*)));
    connect(this, &Form::SendTaskData, taskwindow, &TaskInfo::GetTaskData);

    log.setFileName("log.txt");
    log.open(QIODevice::WriteOnly | QIODevice::Append);

    hoursSearch.setFileName("search.txt");
    hoursSearch.open(QIODevice::ReadWrite | QIODevice::Text);
    streamSearch.setDevice(&hoursSearch);
    hours = streamSearch.readLine().toInt();
    ui->Donelabel->setText("DONE (LAST " + QString::number(hours) + "h)");
    ui->ToDolabel->setText("      TODO (NEXT " + QString::number(hours) + "h)");
    ui->SearchDepth->setText(QString::number(hours));
}

Form::~Form()
{
    delete ui;
    log.close();
    hoursSearch.resize(0);
    streamSearch << hours;
    hoursSearch.close();
}

//GET BACK TO REGISTRATION
void Form::on_SignOutButton_clicked()
{
    ifOpen = false;
    logstream.setDevice(NULL);
    emit backSignal();
}

//PASS NEEDED INFO TO INFO WINDOW
void Form::onTaskClicked(QListWidgetItem* item)
{
    QString data = item->text();
    double id;
    int index = data.length() - 1;
    //FINDING ID WHICH IS AT THE END OF STRING
    while(1)
    {
        if(data[index].isDigit())
        {
            --index;
        }
        else
        {
            break;
        }
    }
    index ++;
    id = data.sliced(index, data.length() - index).toDouble();
    QJsonObject chosen;
    //FINDING OBJECT WHITH THAT ID
    for(const auto& x : VectorData::Tasks)
    {
        if(id == x.value("task_Id").toDouble())
        {
            chosen = x;
            break;
        }
    }
    emit SendTaskData(&chosen, socket);
    taskwindow->show();
}

//SLOT ON WINDOW SHOW
void Form::slot(int id, QTcpSocket *sock, QTextStream *sendlogstream)
{
    socket = sock;
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    ifOpen = true;

    Id = id;

    logstream.setDevice(&*sendlogstream->device());
    sendlogstream->setDevice(NULL);

    Operations::GetTasks(id, socket);
    //Operations::GetUserData(Id, socket);
    //Operations::GetFriends(id, socket);
    //Operations::GetCategories(id, socket);
}

void Form::sockDisc()
{
    socket->deleteLater();
}

//FUNCTION THAT HANDLES INCOMING DATA FROM SERVER
void Form::sockReady()
{
    if(ifOpen)
    {
        if (socket->waitForConnected(500))
        {
            socket->waitForReadyRead(10);
            Data = socket->readAll();
            qDebug() << Data;
            //logstream << LogWriter::Send("test log");
            doc  = QJsonDocument::fromJson(Data, &docError);
            if(docError.errorString().toInt() == QJsonParseError::NoError)
            {
                if (!doc.isArray())
                {
                    //CASE FOR NOT ARRAYS
                    QJsonObject obj = doc.object();
                    //IF IT IS USER DATA
                    if(obj.value("Operation").toString() == "GetUserData")
                    {
                        VectorData::User = obj;
                        DataFillHelper::FillUserData(ui->labelName, ui->labelRankName, ui->labelPoints, ui->RankImg, VectorData::User);
                        Operations::GetCategories(Id, socket);
                    }
                }
                else
                {
                    //IF DATA IS ARRAY
                    QJsonArray array = doc.array();
                    //IF IT IS TASKS
                    if(array[0].toObject().value("task_Id").toDouble() != 0)
                    {
                        VectorData::Tasks.clear();
                        for(const auto &v : array)
                        {
                            QJsonObject obj = v.toObject();
                            VectorData::Tasks.emplace_back(obj);
                        }
                        DataFillHelper::FillWithTasks(ui->ToDo, ui->InProgress, ui->Done, VectorData::Tasks, hours);
                        //CALL GET USER DATA
                        Operations::GetUserData(Id, socket);
                    }
                    //IF IT IS FRIENDS
                    else if(array[0].toObject().value("userID").toDouble() != 0)
                    {
                        VectorData::Friends.clear();
                        for(const auto &v : array)
                        {
                            QJsonObject obj = v.toObject();
                            VectorData::Friends.emplace_back(obj);
                        }
                        //TODO SOME FILL ON FRIENDS
                    }
                    //IF IT IS CATEGORIES
                    else if(array[0].toObject().value("taskCategories_Id").toDouble() != 0)
                    {
                        VectorData::Categories.clear();
                        for(const auto &v : array)
                        {
                            QJsonObject obj = v.toObject();
                            VectorData::Categories.emplace_back(obj);
                        }
                        //TODO SOME LOGIC WITH CATEGORIES
                    }
                    else
                    {
                        qDebug() << "Wrong array data!";
                        return;
                    }
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

//ARCHIVE BUTTON
void Form::on_ArchiveButton_clicked()
{
    if(ui->ArchiveButton->text() == "History")
    {
        ui->ArchiveButton->setText("Back");
        ui->Categorylabel->setText("                          History                 Search:");

        ui->AddTaskButton->setEnabled(false);
        ui->CategoriesButton->setEnabled(false);
        ui->SearchDepth->show();
        ui->SearchDepth->setFont(font);
        ui->SearchDepth->setText("5");
        ui->SearchOk->show();
        ui->Donelabel->setText("DONE (ALL TIME)");
        ui->InProgresslabel->setText("   DELETED");
        ui->ToDolabel->setText("FASTEST COMPLETIONS");
        DataFillHelper::FillWithHistoryTasks(ui->ToDo, ui->InProgress, ui->Done, VectorData::Tasks, 5);
    }
    else
    {
        ui->ArchiveButton->setText("History");
        ui->Categorylabel->setText("                     All Categories                 Last      h");
        DataFillHelper::FillWithTasks(ui->ToDo, ui->InProgress, ui->Done, VectorData::Tasks, hours);
        ui->AddTaskButton->setEnabled(true);
        ui->CategoriesButton->setEnabled(true);
        ui->SearchDepth->setText(QString::number(hours));
        ui->Donelabel->setText("DONE (LAST " + QString::number(hours) + "h)");
        ui->InProgresslabel->setText(" IN PROGRESS");
        ui->ToDolabel->setText("      TODO (NEXT " + QString::number(hours) + "h)");
    }
}


void Form::on_SearchOk_clicked()
{
    if(ui->ArchiveButton->text() == "Back")
    DataFillHelper::FillWithHistoryTasks(ui->ToDo, ui->InProgress, ui->Done, VectorData::Tasks, ui->SearchDepth->text().toInt());
    else
    {
        hours = ui->SearchDepth->text().toInt();
        DataFillHelper::FillWithTasks(ui->ToDo, ui->InProgress, ui->Done, VectorData::Tasks, hours);
        ui->Donelabel->setText("DONE (LAST " + QString::number(hours) + "h)");
        ui->ToDolabel->setText("      TODO (NEXT " + QString::number(hours) + "h)");

    }
}

