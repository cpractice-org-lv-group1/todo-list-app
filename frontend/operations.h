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
    static void GetTasks(const int &id, QTcpSocket *socket);
    static void GetFriends(const int &id, QTcpSocket *socket);
    static void GetUserData(const int &id, QTcpSocket *socket);
    static void GetCategories(const int &id, QTcpSocket *socket);
    static void PostTask(const int &id, QTcpSocket *socket, const QString &header, const QString &body, const QString &starttime, const QString &endtime, const QString &Category, const int &difficulty);
    static void EditTask(QTcpSocket *socket, const QString &header, const QString &body, const QString &starttime,  const QString &endtime, const QString &Category, const int &difficulty, const int &taskid);
    static void DeleteTask(QTcpSocket *socket, const int &taskid);
    static void EditCategory(QTcpSocket *socket, const int &id, const QString &newvalue);
    static void DeleteFriend(QTcpSocket *socket, const int &friendshipid);
    static void ComleteTask(QTcpSocket *socket, const int &userid, const int &newpoints, const int &taskid);
    static void AddCategory(QTcpSocket *socket, const int &userid, const QString &name);
    static void DeleteCategory(QTcpSocket *socket, const int &id);
    static void SendFriendRequest(QTcpSocket *socket, const QString &email, const int &myid);
    static void AnswerFriendRequest(QTcpSocket *socket, const QString &answer, const int &friendshipid);
};

#endif // OPERATIONS_H
