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

void Operations::PostTask(int id, QTcpSocket *socket, QString header, QString body, QString starttime,  QString endtime, QString Category, int difficulty)
{
    QJsonObject NewTask
    {
        {"Operation", "PostTask"},
        {"task_Header", header},
        {"task_Body", body},
        {"task_Start_Time", starttime},
        {"task_Expected_End_Time", endtime},
        {"task_Real_End_Time", "NULL"},
        {"task_Status", "Not Started"},
        {"task_Category", Category},
        {"task_User", id},
        {"task_Difficulty", difficulty},
    };

    QJsonArray jsarray {NewTask};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::EditTask(QTcpSocket *socket, QString header, QString body, QString starttime,  QString endtime, QString Category, int difficulty)
{
    QJsonObject EditTask
    {
        {"Operation", "PutTask"},
        {"task_Header", header},
        {"task_Body", body},
        {"task_Start_Time", starttime},
        {"task_Expected_End_Time", endtime},
        {"task_Category", Category},
        {"task_Difficulty", difficulty},
    };

    QJsonArray jsarray {EditTask};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::DeleteTask(QTcpSocket *socket, int id)
{
    QJsonObject DeleteTask
    {
        {"Operation", "DeleteTask"},
        {"task_Id", id},
    };

    QJsonArray jsarray {DeleteTask};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}










