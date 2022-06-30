#include "Friendships.h"

bool Friendships::Delete(int id)
{
    std::string sqldelete = "Delete from Friendships where friendship_Id = ";
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

bool Friendships::checkAlreadyFriend(int friendship_RequesterId, int addresserId)
{
    //------------------------CHECK ALREADY BE FRIEND---------------------------
    std::string put = "SELECT friendship_Id FROM Friendships\
                       where friendship_RequesterId =";
    put += std::to_string(friendship_RequesterId) +
        " and friendship_AdresserId =";
    put += std::to_string(addresserId) + " and (friendship_Status = 1 or friendship_Status = 2)";
        std::wstring wput = GetWCharFromString(put);
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

    int friendshipId = 0;

    if (retcode == SQL_SUCCESS)
    {
        retcode = SQLFetch(sqlStmtHandle);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "Error reading query!\n";
            Logger("{Friendships.cpp//Friendships::checkAlreadyFriend} Error reading query to add new friend!");
            return false;
        }
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &friendshipId, 0, &lenth);
        }
    }
    else
    {
        Logger("{Friendships.cpp//Friendships::checkAlreadyFriend} Query is failed!");
        return false;
    }

    if (friendshipId != 0) 
    {
        std::string str = "This userId: " + std::to_string(friendship_RequesterId) + " ALREADY has a requst/friend #"+ std::to_string(addresserId);
        Logger(str);
        SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
        return true;
    }
    else
    {
        SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
        return false;
    }
}

std::vector<Friendships::FriendshipsStruct> Friendships::GetData() const
{
    return AllFriendships;
}

std::vector<Friendships::FriendStruct> Friendships::GetAllFriends() const
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
                std::cout << "Error reading query!\n";
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
        std::cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

void Friendships::Get(int userId)
{
    std::string put = "select u.user_Id, u.user_Name, u.user_Surname, u.user_Birthday, u.user_Mail, \
                       u.user_Points, u.user_Rank, fs.friend_status_Name, fr.friendship_ResponceTime,\
        fr.friendship_Id\
        from Friendships fr\
        left join Users u on(user_Id = fr.friendship_AdresserId and user_Id != ";
    put += std::to_string(userId) + ") or (user_Id = fr.friendship_RequesterId and user_Id !=";
    put += std::to_string(userId) + ")\
        left join FriendStatuses fs on fr.friendship_Status = fs.friend_status_Id\
        where(fr.friendship_AdresserId = ";
    put += std::to_string(userId) + " and fs.friend_status_Name = 'waiting for responce')\
        or (fr.friendship_RequesterId = ";
    put += std::to_string(userId) + " and fs.friend_status_Name = 'added') or (fr.friendship_AdresserId = ";
    put += std::to_string(userId) + " and fs.friend_status_Name = 'added')\
        and user_Id != ";
    put += std::to_string(userId);
    std::wstring wput = GetWCharFromString(put);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

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
                SQLGetData(sqlStmtHandle, 10, SQL_C_ULONG, &userFriend.friendship_Id, 0, &lenth);

                AllFriends.emplace_back(userFriend);
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

bool Friendships::Post(const nlohmann::json& newObject)
{
    //----------------------CHECK VALID EMAIL-------------------------------------
    std::string put = "SELECT user_Id FROM USERS where user_Mail ='";
    put += newObject["user_Mail"].get<std::string>() + "'";
    std::wstring wput = GetWCharFromString(put);
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

    int addresserId = 0;

    if (retcode == SQL_SUCCESS)
    {
        retcode = SQLFetch(sqlStmtHandle);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "Error reading query!\n";
            Logger("{Friendships.cpp//Friendships::Post} Error reading query to add new friend!");
            return false;
        }
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &addresserId, 0, &lenth);
        }
    }
    else 
    {
        Logger("{Friendships.cpp//Friendships::Post} Query is failed!");
        return false;
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);


    //--------------------------POST FRIEND----------------------------------------
    if (addresserId != 0 && checkAlreadyFriend(newObject["friendship_RequesterId"].get<int>(), addresserId) == false)
    {
        std::string insert = "INSERT INTO Friendships VALUES(";
        put += std::to_string(newObject["friendship_RequesterId"].get<int>()) + "," +
            std::to_string(addresserId) + ", GETDATE()" + ", NULL, " +
            std::to_string(1) + ");";

        std::wstring winsert = GetWCharFromString(insert);
        retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)winsert.c_str(), SQL_NTS);

        if (retcode == SQL_SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else 
    {
        Logger("{Friendships.cpp//Friendships::Post} User Email did not find!");
        return false;
    }
}

bool Friendships::Put(const nlohmann::json &newObject)
{
    int friendship_Status;
    if (newObject["Answer"].get<std::string>() == "yes")
    {
        friendship_Status = 2;
    }
    else
    {
        friendship_Status = 3;
    }
    std::string put = "UPDATE Friendships SET ";
    put += "friendship_Status = " + std::to_string(friendship_Status) + ", friendship_ResponceTime = GETDATE()"
        " where friendship_Id = " + std::to_string(newObject["friendship_Id"].get<int>()) ;

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
