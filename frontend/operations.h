#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

class Operations
{
public:
    Operations();
    static void GetTasks(int id, QTcpSocket *socket);
    static void GetFriends(int id, QTcpSocket *socket);
    static void GetUserData(int id, QTcpSocket *socket);
    static void GetCategories(int id, QTcpSocket *socket);
    static void PostTask(int id, QTcpSocket *socket, QString header, QString body, QString starttime,  QString endtime, QString Category, int difficulty);
};

#endif // OPERATIONS_H
