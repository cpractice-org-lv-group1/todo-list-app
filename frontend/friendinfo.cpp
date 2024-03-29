#include "friendinfo.h"
#include "ui_friendinfo.h"

FriendInfo::FriendInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);
}

FriendInfo::~FriendInfo()
{
    delete ui;
}

void FriendInfo::GetFriendData(QJsonObject *obj, QTcpSocket *sock)
{
    socket = sock;
    currentUser = *obj;
    font.setPointSize(16);

    //STYLES
    this->setStyleSheet("QMainWindow{background-color: white;}");
    ui->Accept->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->Reject->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid red;}");
    ui->Delete->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid red;}");
    ui->NameSurname->setFont(font);

    //DISPLAY INFO
    if(currentUser.value("friend_status_Name").toString() == "added")
    {
        ui->Accept->hide();
        ui->Reject->hide();
        ui->Delete->show();
        this->setFixedSize(267,215);
        ui->FriendsSince->show();
        ui->FriendsSince->setText("Friends since: " + currentUser.value("friendship_ResponceTime").toString("yyyy-MM-dd").sliced(0, 10));
    }
    else
    {
        ui->Accept->show();
        ui->Reject->show();
        ui->Delete->hide();
        this->setFixedSize(267,190);
        ui->FriendsSince->hide();
    }
    QString rankName = currentUser.value("user_Rank").toString();
    ui->NameSurname->setText(currentUser.value("user_Name").toString() + " " + currentUser.value("user_Surname").toString());
    ui->RankName->setText("Rank: " + rankName);
    ui->Points->setText("Points: " + QString::number(currentUser.value("user_Points").toDouble()));
    if(rankName == "Novice")
    {
        QPixmap pix(":/Img/Ranks/silver.png");
        ui->RankIcon->setPixmap(pix);
    }
    else if(rankName == "Gold")
    {
        QPixmap pix(":/Img/Ranks/gold.png");
        ui->RankIcon->setPixmap(pix);
    }
    else if(rankName == "Platinum")
    {
        QPixmap pix(":/Img/Ranks/platinum.png");
        ui->RankIcon->setPixmap(pix);
    }
    else if(rankName == "Diamomd")
    {
        QPixmap pix(":/Img/Ranks/diamond.png");
        ui->RankIcon->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/Img/Ranks/immortal.png");
        ui->RankIcon->setPixmap(pix);
    }
    ui->Email->setText("Email: " + currentUser.value("user_Mail").toString());
    ui->Birthday->setText("Birthday: " + currentUser.value("user_Birthday").toString());
}

void FriendInfo::on_Delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this task?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Operations::DeleteFriend(socket, currentUser.value("friendship_Id").toDouble());
    }


}

void FriendInfo::on_Reject_clicked()
{
    Operations::AnswerFriendRequest(socket, "no", currentUser.value("friendship_Id").toDouble());
}


void FriendInfo::on_Accept_clicked()
{
    Operations::AnswerFriendRequest(socket, "yes", currentUser.value("friendship_Id").toDouble());
}

