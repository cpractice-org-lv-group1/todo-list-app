#include "Friendships.h"

vector<Friendships::FriendshipsStruct> Friendships::GetData()
{
    return AllFriendships;
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

void Friendships::Get(int idUser)
{

}
