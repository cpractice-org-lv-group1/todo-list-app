#include "operations.h"

Operations::Operations()
{

}

void Operations::GetTasks(const int &id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetTasks"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::GetFriends(const int &id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetUserFriends"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::GetCategories(const int &id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetCategories"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::GetUserData(const int &id, QTcpSocket *socket)
{
    QJsonObject GetById
    {
        {"Operation", "GetUserData"},
        {"Id", id}
    };

    QJsonArray jsarray {GetById};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::PostTask(const int &id, QTcpSocket *socket, const QString &header, const QString &body, const QString &starttime,
                          const QString &endtime, const QString &Category, const int &difficulty)
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

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::EditTask(QTcpSocket *socket, const QString &header, const QString &body, const QString &starttime,  const QString &endtime, const QString &Category,
                          const int &difficulty, const int &taskid)
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

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::DeleteTask(QTcpSocket *socket, const int &taskid)
{
    QJsonObject DeleteTask
    {
        {"Operation", "DeleteTask"},
        {"task_Id", taskid},
    };

    QJsonArray jsarray {DeleteTask};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::EditCategory(QTcpSocket *socket, const int &id, const QString &newvalue)
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

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::DeleteFriend(QTcpSocket *socket, const int &friendshipid)
{
    QJsonObject DeleteFriend
    {
        {"Operation", "DeleteFriend"},
        {"friendship_Id", friendshipid},
    };

    QJsonArray jsarray {DeleteFriend};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::ComleteTask(QTcpSocket *socket, const int &userid, const int &newpoints, const int &taskid)
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

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::AddCategory(QTcpSocket *socket, const int &userid, const QString &name)
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

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::DeleteCategory(QTcpSocket *socket, const int &id)
{
    QJsonObject DeleteCategory
    {
        {"Operation", "DeleteCategory"},
        {"taskCategories_Id", id},
    };

    QJsonArray jsarray {DeleteCategory};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::SendFriendRequest(QTcpSocket *socket, const QString &email, const int &myid)
{
    QJsonObject SendFriendRequest
    {
        {"Operation", "AddFriend"},
        {"user_Mail", email},
        {"friendship_RequesterId", myid},
    };

    QJsonArray jsarray {SendFriendRequest};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}

void Operations::AnswerFriendRequest(QTcpSocket *socket, const QString &answer, const int &friendshipid)
{
    QJsonObject AnswerFriendRequest
    {
        {"Operation", "FriendRequestAnswer"},
        {"Answer", answer},
        {"friendship_Id", friendshipid},
    };

    QJsonArray jsarray {AnswerFriendRequest};
    QJsonDocument jsDoc(jsarray);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    if(socket->isOpen())
    {
        socket-> write(jsString.toLatin1());
    }
}











