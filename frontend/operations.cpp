#include "operations.h"

Operations::Operations()
{

}

void Operations::GetTasks(int id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetTasks"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }

   // qDebug() << formatted;
}

void Operations::GetFriends(int id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetUserFriends"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }

    //qDebug() << formatted;
}

void Operations::GetCategories(int id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetCategories"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }

    //qDebug() << formatted;
}

void Operations::GetUserData(int id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetUserData"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }

    //qDebug() << formatted;
}
