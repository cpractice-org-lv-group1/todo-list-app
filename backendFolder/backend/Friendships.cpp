#include "Friendships.h"

void Friendships::Delete(int id)
{
    string sqldelete = "Delete from Friendships where friendship_Id = ";
    sqldelete += to_string(id);

    wstring wsqldelete = GetWCharFromString(sqldelete);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
}

vector<Friendships::FriendshipsStruct> Friendships::GetData()
{
    return AllFriendships;
}

vector<Friendships::FriendStruct> Friendships::GetAllFriends()
{
    return this->AllFriends;
}


void Friendships::Get()
{
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Friendships", SQL_NTS);

    if (retcode == SQL_SUCCESS)
    {
        while (true)
        {
            retcode = SQLFetch(sqlStmtHandle);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            {
                cout << "Error reading query!\n";
            }
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                FriendshipsStruct newFriendship;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newFriendship.friendship_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_ULONG, &newFriendship.friendship_RequesterId, 0, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_ULONG, &newFriendship.friendship_AdresserId, 0, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newFriendship.friendship_RequestTime, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newFriendship.friendship_ResponceTime, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_ULONG, &newFriendship.friendship_Status, 0, &lenth);

                AllFriendships.emplace_back(newFriendship);
            }
            else break;
        }
    }
    else
    {
        cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

void Friendships::Get(int userId)
{
    string put = "select u.user_Id, u.user_Name, u.user_Surname, u.user_Birthday, u.user_Mail, u.user_Points, u.user_Rank, fs.friend_status_Name, fr.friendship_ResponceTime\
        from Friendships fr\
        left join Users u on(user_Id = fr.friendship_AdresserId and user_Id != ";
    put += to_string(userId) + ") or (user_Id = fr.friendship_RequesterId and user_Id !=";
    put += to_string(userId) + ")\
        left join FriendStatuses fs on fr.friendship_Status = fs.friend_status_Id\
        where(fr.friendship_AdresserId = ";
    put += to_string(userId) + " and fs.friend_status_Name = 'waiting for responce')\
        or (fr.friendship_RequesterId = ";
    put += to_string(userId) + " and fs.friend_status_Name = 'added') or (fr.friendship_AdresserId = ";
    put += to_string(userId) + " and fs.friend_status_Name = 'added')\
        and user_Id != ";
    put += to_string(userId); 
    wstring wput = GetWCharFromString(put);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

    if (retcode == SQL_SUCCESS)
    {
        while (true)
        {
            retcode = SQLFetch(sqlStmtHandle);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            {
                cout << "Error reading query!\n";
            }
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                FriendStruct userFriend;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &userFriend.user_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, userFriend.user_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, userFriend.user_Surname, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, userFriend.user_Birthday, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, userFriend.user_Mail, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_ULONG, &userFriend.user_Points, 0, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_CHAR, userFriend.user_Rank, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, userFriend.friend_status_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 9, SQL_C_CHAR, userFriend.friendship_ResponceTime, FIELD_LEN, &lenth);

                AllFriends.emplace_back(userFriend);
            }
            else break;
        }
    }
    else
    {
        cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}
