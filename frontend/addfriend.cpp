#include "addfriend.h"
#include "ui_addfriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    this->setFixedSize(243,130);
}

AddFriend::~AddFriend()
{
    delete ui;
}

//SLOT ON WINDOW SHOW
void AddFriend::GetToAddFriend(QTcpSocket *sock, int id)
{
    socket = sock;
    Id = id;
    font.setPointSize(14);

    //STYLES
    this->setStyleSheet("QMainWindow{background-color: white;} QLinetEdit {border: 1px solid black;} QLineEdit:focus { border: 1px solid darkgreen;}");
    ui->pushButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->Error->setStyleSheet("color: red");
    ui->Error->hide();
    ui->lineEdit->setFont(font);

}

void AddFriend::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->Error->show();
    }
    else
    {
        ui->Error->hide();
        //SEARCH FOR THAT FRIEND
    }
}

