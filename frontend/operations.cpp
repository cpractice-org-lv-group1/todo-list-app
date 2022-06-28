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

void Operations::EditTask(QTcpSocket *socket, QString header, QString body, QString starttime,  QString endtime, QString Category, int difficulty, int taskid)
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
        {"task_Id", taskid},
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

void Operations::DeleteTask(QTcpSocket *socket, int taskid)
{
    QJsonObject DeleteTask
    {
        {"Operation", "DeleteTask"},
        {"task_Id", taskid},
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

void Operations::EditCategory(QTcpSocket *socket, int id, QString newvalue)
{
    QJsonObject EditCategory
    {
        {"Operation", "PutCategory"},
        {"taskCategories_Id", id},
        {"taskCategories_Name", newvalue},
    };

    QJsonArray jsarray {EditCategory};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::DeleteFriend(QTcpSocket *socket, int friendshipid)
{
    QJsonObject DeleteFriend
    {
        {"Operation", "DeleteFriend"},
        {"friendship_Id", friendshipid},
    };

    QJsonArray jsarray {DeleteFriend};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::ComleteTask(QTcpSocket *socket, int userid, int newpoints, int taskid)
{
    QJsonObject ComleteTask
    {
        {"Operation", "CompleteTask"},
        {"user_Id", userid},
        {"user_Points", newpoints},
        {"task_Id", taskid},
    };

    QJsonArray jsarray {ComleteTask};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::AddCategory(QTcpSocket *socket, int userid, QString name)
{
    QJsonObject AddCategory
    {
        {"Operation", "PostCategory"},
        {"taskCategories_User", userid},
        {"taskCategories_Name", name},
    };

    QJsonArray jsarray {AddCategory};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::DeleteCategory(QTcpSocket *socket, int id)
{
    QJsonObject DeleteCategory
    {
        {"Operation", "DeleteCategory"},
        {"taskCategories_Id", id},
    };

    QJsonArray jsarray {DeleteCategory};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    QJsonDocument doc = QJsonDocument::fromJson(jsString.toUtf8());
    QString formatted = doc.toJson(QJsonDocument::Compact);

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}










