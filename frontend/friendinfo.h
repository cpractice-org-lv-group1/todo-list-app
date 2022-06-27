#ifndef FRIENDINFO_H
#define FRIENDINFO_H

#include <QMainWindow>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QMessageBox>
#include <vector>
#include "operations.h"

namespace Ui {
class FriendInfo;
}

class FriendInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendInfo(QWidget *parent = nullptr);
    ~FriendInfo();
    QFont font;
    QTcpSocket* socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

public slots:
    void GetFriendData(QJsonObject *obj, QTcpSocket *sock);


private slots:
    void on_Delete_clicked();

private:
    Ui::FriendInfo *ui;
    QJsonObject currentUser;
};

#endif // FRIENDINFO_H
