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
    static void EditTask(QTcpSocket *socket, QString header, QString body, QString starttime,  QString endtime, QString Category, int difficulty, int taskid);
    static void DeleteTask(QTcpSocket *socket, int taskid);
    static void EditCategory(QTcpSocket *socket, int id, QString newvalue);
    static void DeleteFriend(QTcpSocket *socket, int friendshipid);
    static void ComleteTask(QTcpSocket *socket, int userid, int newpoints, int taskid);
    static void AddCategory(QTcpSocket *socket, int userid, QString name);
    static void DeleteCategory(QTcpSocket *socket, int id);
    static void SendFriendRequest(QTcpSocket *socket, QString email, int myid);
    static void AnswerFriendRequest(QTcpSocket *socket, QString answer, int friendshipid);
};

#endif // OPERATIONS_H
