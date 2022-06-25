#include "taskinfo.h"
#include "ui_taskinfo.h"

TaskInfo::TaskInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaskInfo)
{
    ui->setupUi(this);

    //STYLES
    ui->NoneLabel->hide();
    this->setFixedSize(590,309);
}

TaskInfo::~TaskInfo()
{
    delete ui;
}

void TaskInfo::GetTaskData(QJsonObject *obj,const vector<QJsonObject> &categories, QTcpSocket *sock)
{
    socket = sock;
    currentTask = *obj;
    font.setPointSize(14);

    //SET DATA
    ui->TaskHeader->setText(currentTask.value("task_Header").toString());
    ui->TaskDescription->setText(currentTask.value("task_Body").toString());
    //start time
    QString sDate = currentTask.value("task_Start_Time").toString().sliced(0, 16);
    QDateTime qDate = QDateTime::fromString(sDate,"yyyy-MM-dd hh:mm");
    ui->TaskStartTime->setDateTime(qDate);
    //expected time
    sDate = currentTask.value("task_Expected_End_Time").toString().sliced(0, 16);
    qDate = QDateTime::fromString(sDate,"yyyy-MM-dd hh:mm");
    ui->TaskExpEnd->setDateTime(qDate);
    //real end time
    if( currentTask.value("task_Real_End_Time").toString()!= "None")
    {
        ui->NoneLabel->hide();
        ui->TaskEnd->show();
        sDate = currentTask.value("task_Real_End_Time").toString().sliced(0, 16);
        qDate = QDateTime::fromString(sDate,"yyyy-MM-dd hh:mm");
        ui->TaskEnd->setDateTime(qDate);
    }
    else
    {
        ui->NoneLabel->show();
        ui->NoneLabel->setFont(font);
        ui->TaskEnd->hide();
    }
    ui->TaskStatus->setText(currentTask.value("task_Status").toString());
    ui->TaskDifficulty->setText(QString::number(currentTask.value("task_Difficulty").toDouble()));

    ui->comboBox->clear();
    for(auto &x : categories)
    {
        ui->comboBox->addItem(x.value("taskCategories_Name").toString());
    }

    //SET STYLE
    ui->comboBox->setFont(font);
    ui->comboBox->setEnabled(false);
    ui->comboBox->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;} QComboBox:!enabled{color:black}");
    ui->EditButton->setEnabled(true);
    ui->DoneButton->setEnabled(true);
    ui->DeleteButton->setEnabled(true);
    this->setStyleSheet("QMainWindow{background-color: white;} QTextEdit {border: none; } QDateTimeEdit {border: none; } QComboBox{border: none;}");
    ui->TaskHeader->setReadOnly(true);
    ui->TaskHeader->setFont(font);
    ui->TaskDescription->setReadOnly(true);
    ui->TaskDescription->setFont(font);
    ui->TaskStartTime->setReadOnly(true);
    ui->TaskStartTime->setFont(font);
    ui->TaskExpEnd->setReadOnly(true);
    ui->TaskExpEnd->setFont(font);
    ui->TaskEnd->setReadOnly(true);
    ui->TaskEnd->setFont(font);
    ui->TaskStatus->setReadOnly(true);
    ui->TaskStatus->setFont(font);
    ui->TaskDifficulty->setReadOnly(true);
    ui->TaskDifficulty->setFont(font);
    ui->EditButton->setText("Edit");

    //DIFFERENT CASES FOR STATUSES
    if(currentTask.value("task_Status").toString() == "Completed")
    {
        ui->EditButton->setEnabled(false);
        ui->DoneButton->setEnabled(false);
    }
    else if(currentTask.value("task_Status").toString() == "Deleted")
    {
        ui->EditButton->setEnabled(false);
        ui->DoneButton->setEnabled(false);
        ui->DeleteButton->setEnabled(false);
    }
}

void TaskInfo::on_EditButton_clicked()
{
    if(ui->EditButton->text() == "Edit")
    {
        ui->comboBox->setEnabled(true);
        ui->TaskHeader->setReadOnly(false);
        ui->TaskDescription->setReadOnly(false);
        ui->TaskStartTime->setReadOnly(false);
        ui->TaskExpEnd->setReadOnly(false);
        ui->TaskEnd->setReadOnly(false);
        ui->TaskDifficulty->setReadOnly(false);
        ui->EditButton->setText("Ok");
        ui->EditButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
        this->setStyleSheet("QMainWindow{background-color: white;} QTextEdit {border: 1px solid black; } QDateTimeEdit {border: 1px solid black; } QComboBox{border: 1px solid black;}");
        ui->TaskStatus->setStyleSheet("QTextEdit {border: none; }");
        ui->TaskEnd->setStyleSheet("QDateTimeEdit {border: none; }");
    }
    else
    {
        ui->comboBox->setEnabled(false);
        ui->TaskHeader->setReadOnly(true);
        ui->TaskDescription->setReadOnly(true);
        ui->TaskStartTime->setReadOnly(true);
        ui->TaskExpEnd->setReadOnly(true);
        ui->TaskEnd->setReadOnly(true);
        ui->TaskDifficulty->setReadOnly(true);
        ui->EditButton->setText("Edit");
        ui->EditButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid blue;}");
        this->setStyleSheet("QMainWindow{background-color: white;} QTextEdit {border: none; } QDateTimeEdit {border: none; } QComboBox{border: none;}");

        //TODO MAKE EDIT OPERATION
    }
}

