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
};

#endif // OPERATIONS_H
