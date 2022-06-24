#include "FriendStatuses.h"

void FriendStatuses::Delete(int id)
{
    string sqldelete = "Delete from FriendStatuses where friend_status_Id = ";
    sqldelete += to_string(id);

    wstring wsqldelete = GetWCharFromString(sqldelete);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
}

vector<FriendStatuses::FriendStatusesStruct> FriendStatuses::GetData()
{
    return AllFriendStatuses;
}


void FriendStatuses::Get()
{
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM FriendStatuses", SQL_NTS);

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
                FriendStatusesStruct newFriendStatus;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newFriendStatus.friend_status_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newFriendStatus.friend_status_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newFriendStatus.friend_status_Description, FIELD_LEN, &lenth);

                AllFriendStatuses.emplace_back(newFriendStatus);
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
