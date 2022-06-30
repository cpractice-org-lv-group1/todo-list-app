#include "FriendStatuses.h"

bool FriendStatuses::Delete(int id)
{
    std::string sqldelete = "Delete from FriendStatuses where friend_status_Id = ";
    sqldelete += std::to_string(id);

    std::wstring wsqldelete = GetWCharFromString(sqldelete);

    if (SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS) == SQL_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<FriendStatuses::FriendStatusesStruct> FriendStatuses::GetData() const
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
                std::cout << "Error reading query!\n";
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
        std::cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

bool FriendStatuses::Post(const nlohmann::json& newObject)
{
    std::string put = "INSERT INTO FriendStatuses VALUES('";
    put += newObject["friend_status_Name"].get<std::string>() + "', '" +
        newObject["friend_status_Description"].get<std::string>() + "');";

    std::wstring wput = GetWCharFromString(put);

    if (SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS) == SQL_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
