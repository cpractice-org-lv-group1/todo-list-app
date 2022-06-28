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

void TaskInfo::GetTaskData(QJsonObject *obj,const vector<QJsonObject> &categories, QTcpSocket *sock, int points)
{
    socket = sock;
    currentTask = *obj;
    font.setPointSize(14);
    userpoints = points;

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

    //FILL COMBOBOXES
    ui->TaskCategory->clear();
    for(auto &x : categories)
    {
        ui->TaskCategory->addItem(x.value("taskCategories_Name").toString());
    }
    ui->TaskDifficulty->clear();
    for(int i = 0; i < 10; ++i)
    {
        ui->TaskDifficulty->addItem(QString::number(i+1), (double)i+1);
    }
    ui->TaskCategory->setCurrentText(currentTask.value("task_Category").toString());
    int index = ui->TaskDifficulty->findData(currentTask.value("task_Difficulty").toDouble());
    if ( index != -1 ) ui->TaskDifficulty->setCurrentIndex(index);

    //LOGIC FOR POINTS
    currentpoints = (QDateTime::fromString(currentTask.value("task_Expected_End_Time").toString().sliced(0, 16), "yyyy-MM-dd hh:mm").toSecsSinceEpoch() -
                QDateTime::fromString(currentTask.value("task_Start_Time").toString().sliced(0, 16), "yyyy-MM-dd hh:mm").toSecsSinceEpoch()) *
             currentTask.value("task_Difficulty").toDouble() / (3600*10);

    if(QDateTime::currentDateTime() > QDateTime::fromString(currentTask.value("task_Expected_End_Time").toString().sliced(0, 16), "yyyy-MM-dd hh:mm"))
        currentpoints = currentpoints/2;

    //SET STYLE
    ui->HeaderError->setStyleSheet("color: red");
    ui->BodyError->setStyleSheet("color: red");
    ui->TimeError->setStyleSheet("color: red");
    ui->HeaderError->hide();
    ui->BodyError->hide();
    ui->TimeError->hide();
    ui->TaskCategory->setFont(font);
    ui->TaskCategory->setEnabled(false);
    ui->TaskCategory->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;} QComboBox:!enabled{color:black}");
    ui->TaskDifficulty->setFont(font);
    ui->TaskDifficulty->setEnabled(false);
    ui->TaskDifficulty->setStyleSheet ("QComboBox::drop-down {border-width: 0px;} QComboBox::down-arrow {image: url(noimg); border-width: 0px;} QComboBox:!enabled{color:black}");
    ui->EditButton->setEnabled(true);
    ui->DoneButton->setEnabled(true);
    ui->DoneButton_2->setEnabled(true);
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
    ui->EditButton->setText("Edit");
    ui->DonePoints->setText("Points:\n+ " + QString::number(currentpoints));
    ui->DonePoints_2->setText("Points:\n+ " + QString::number(currentpoints/2));

    //DIFFERENT CASES FOR STATUSES
    if(currentTask.value("task_Status").toString() == "Completed")
    {
        ui->EditButton->setEnabled(false);
        ui->DoneButton->setEnabled(false);
        ui->DoneButton_2->setEnabled(false);
        ui->DonePoints->setText("Points:\n  + 0");
        ui->DonePoints_2->setText("Points:\n  + 0");

    }
    else if(currentTask.value("task_Status").toString() == "Deleted")
    {
        ui->EditButton->setEnabled(false);
        ui->DoneButton->setEnabled(false);
        ui->DoneButton_2->setEnabled(false);
        ui->DeleteButton->setEnabled(false);
        ui->DonePoints->setText("Points:\n  + 0");
        ui->DonePoints_2->setText("Points:\n  + 0");
    }
}

void TaskInfo::on_EditButton_clicked()
{
    if(ui->EditButton->text() == "Edit")
    {
        ui->HeaderError->hide();
        ui->BodyError->hide();
        ui->TimeError->hide();
        ui->TaskCategory->setEnabled(true);
        ui->TaskDifficulty->setEnabled(true);
        ui->TaskHeader->setReadOnly(false);
        ui->TaskDescription->setReadOnly(false);
        ui->TaskStartTime->setReadOnly(false);
        ui->TaskExpEnd->setReadOnly(false);
        ui->TaskEnd->setReadOnly(false);
        ui->EditButton->setText("Ok");
        ui->EditButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
        this->setStyleSheet("QMainWindow{background-color: white;} QTextEdit {border: 1px solid black; } QTextEdit:focus { border: 1px solid darkgreen;}"
                            "QDateTimeEdit {border: 1px solid black; } QDateTimeEdit:focus { border: 1px solid darkgreen;}"
                            "QComboBox{border: 1px solid black;} QComboBox:focus { border: 1px solid darkgreen;}");
        ui->TaskStatus->setStyleSheet("QTextEdit {border: none; }");
        ui->TaskEnd->setStyleSheet("QDateTimeEdit {border: none; }");
    }
    else
    {
        //IF ALL FIELDS ARE GOOD
        if( !ui->TaskHeader->toPlainText().isEmpty() && !ui->TaskDescription->toPlainText().isEmpty() && (ui->TaskStartTime->dateTime() < ui->TaskExpEnd->dateTime()))
        {
            ui->HeaderError->hide();
            ui->BodyError->hide();
            ui->TimeError->hide();

            ui->TaskCategory->setEnabled(false);
            ui->TaskDifficulty->setEnabled(false);
            ui->TaskHeader->setReadOnly(true);
            ui->TaskDescription->setReadOnly(true);
            ui->TaskStartTime->setReadOnly(true);
            ui->TaskExpEnd->setReadOnly(true);
            ui->TaskEnd->setReadOnly(true);
            ui->EditButton->setText("Edit");
            ui->EditButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid blue;}");
            this->setStyleSheet("QMainWindow{background-color: white;} QTextEdit {border: none; } QDateTimeEdit {border: none; } QComboBox{border: none;}");

            //COUNT NEW POINTS
            currentpoints = (ui->TaskExpEnd->dateTime().toSecsSinceEpoch() -
                        ui->TaskStartTime->dateTime().toSecsSinceEpoch()) *
                    ui->TaskDifficulty->currentText().toInt() / (3600*10);

            if(QDateTime::currentDateTime() > ui->TaskExpEnd->dateTime())
                currentpoints = currentpoints/2;

            ui->DonePoints->setText("Points:\n+ " + QString::number(currentpoints));
            ui->DonePoints_2->setText("Points:\n+ " + QString::number(currentpoints/2));


            //TODO MAKE EDIT OPERATION
            Operations::EditTask(socket, ui->TaskHeader->toPlainText(), ui->TaskDescription->toPlainText(), ui->TaskStartTime->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                                ui->TaskExpEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),ui->TaskCategory->currentText(), ui->TaskDifficulty->currentText().toInt(),
                                 currentTask.value("task_Id").toDouble());
        }
        else
        {
            bool ifHeaderError = false;
            bool ifBodyError = false;
            bool ifTimeError = false;

            if(ui->TaskHeader->toPlainText().isEmpty()) ifHeaderError = true;
            if(ui->TaskDescription->toPlainText().isEmpty()) ifBodyError = true;
            if(ui->TaskStartTime->dateTime() >= ui->TaskExpEnd->dateTime()) ifTimeError = true;

            ui->HeaderError->hide();
            ui->BodyError->hide();
            ui->TimeError->hide();

            if(ifHeaderError) ui->HeaderError->show();
            if(ifBodyError) ui->BodyError->show();
            if(ifTimeError) ui->TimeError->show();
        }

    }
}


void TaskInfo::on_DeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this task?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Operations::DeleteTask(socket, currentTask.value("task_Id").toDouble());
    }
}


void TaskInfo::on_DoneButton_clicked()
{
    Operations::ComleteTask(socket, currentTask.value("task_User").toDouble(), (userpoints + currentpoints), currentTask.value("task_Id").toDouble());
}


void TaskInfo::on_DoneButton_2_clicked()
{
    Operations::ComleteTask(socket, currentTask.value("task_User").toDouble(), (userpoints + (currentpoints/2)), currentTask.value("task_Id").toDouble());
}

