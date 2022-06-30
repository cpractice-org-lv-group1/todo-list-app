#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddTask)
{
    ui->setupUi(this);
    this->setFixedSize(240,409);
}

AddTask::~AddTask()
{
    delete ui;
}

//SLOT ON WINDOW SHOW
void AddTask::GetToAddTask(QTcpSocket *sock, const int &id, const vector<QJsonObject> &categories)
{
    socket = sock;
    Id = id;
    font.setPointSize(14);

    //STYLES
    ui->Category->clear();
    for(auto &x : categories)
    {
        ui->Category->addItem(x.value("taskCategories_Name").toString());
    }
    ui->Difficulty->clear();
    for(int i = 0; i < 10; ++i)
    {
        ui->Difficulty->addItem(QString::number(i+1));
    }
    ui->StartTime->setDateTime(QDateTime::currentDateTime());
    ui->ExpEndTime->setDateTime(QDateTime::currentDateTime());

    ui->Header->setFont(font);
    ui->Body->setFont(font);
    ui->StartTime->setFont(font);
    ui->ExpEndTime->setFont(font);
    ui->Category->setFont(font);
    ui->Difficulty->setFont(font);
    ui->Category->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;} QComboBox:!enabled{color:black}");
    ui->Difficulty->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;} QComboBox:!enabled{color:black}");
    ui->AddButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    this->setStyleSheet("QMainWindow{background-color: white;} QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;} "
                        "QLineEdit {border: 1px solid black; } QLineEdit:focus { border: 1px solid darkgreen;}"
                        "QDateTimeEdit {border: 1px solid black; } QDateTimeEdit:focus { border: 1px solid darkgreen;}"
                        "QComboBox{border: 1px solid black;} QComboBox:focus { border: 1px solid darkgreen;}");
    ui->HeaderError->setStyleSheet("color: red");
    ui->DescriptionError->setStyleSheet("color: red");
    ui->EndTimeError->setStyleSheet("color: red");
    ui->HeaderError->hide();
    ui->DescriptionError->hide();
    ui->EndTimeError->hide();
}

void AddTask::on_AddButton_clicked()
{
    //IF ALL GOOD
    if( !ui->Header->text().isEmpty() && !ui->Body->toPlainText().isEmpty() && (ui->StartTime->dateTime() < ui->ExpEndTime->dateTime()))
    {
        ui->HeaderError->hide();
        ui->DescriptionError->hide();
        ui->EndTimeError->hide();
        //POST METHOD

        Operations::PostTask(Id, socket,ui->Header->text(), ui->Body->toPlainText(), ui->StartTime->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                             ui->ExpEndTime->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->Category->currentText(), ui->Difficulty->currentText().toInt());

    }
    else
    {
        bool ifHeaderError = false;
        bool ifBodyError = false;
        bool ifTimeError = false;

        if(ui->Header->text().isEmpty()) ifHeaderError = true;
        if(ui->Body->toPlainText().isEmpty()) ifBodyError = true;
        if(ui->StartTime->dateTime() >= ui->ExpEndTime->dateTime()) ifTimeError = true;

        ui->HeaderError->hide();
        ui->DescriptionError->hide();
        ui->EndTimeError->hide();

        if(ifHeaderError) ui->HeaderError->show();
        if(ifBodyError) ui->DescriptionError->show();
        if(ifTimeError) ui->EndTimeError->show();

    }
}

