#include "Users.h"

vector<Users::UsersStruct> Users::GetData()
{
    return AllUsers;
}
Users::UsersStruct Users::GetCurrentUser()
{
    return currentUser;
}

Users::UsersStruct Users::GetCurrentData()
{
    return currentData;
}

void Users::Get(string email) 
{
    string put = "SELECT * FROM USERS where user_Mail ='";
           put += email+"'";
    wstring wput = GetWCharFromString(put);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

    if (retcode == SQL_SUCCESS)
    {
        retcode = SQLFetch(sqlStmtHandle);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
        {
            cout << "Error reading query!\n";
        }
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            UsersStruct newUser;
            SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newUser.userID, 0, &lenth);
            SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newUser.userNameArr, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newUser.userSurnameArr, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newUser.userBithday, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newUser.userMail, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newUser.userPassword, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 7, SQL_C_ULONG, &newUser.userPoints, 0, &lenth);
            SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, newUser.userRank, FIELD_LEN, &lenth);

            currentUser = newUser;
        }
    }
    else
    {
        cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

bool Users::Post(nlohmann::json newObject)
{  
    string put = "SELECT user_Id FROM USERS where user_Mail ='"; //CHECK VALID EMAIL
    put += newObject["user_Mail"].get<string>() + "'";
    wstring wput = GetWCharFromString(put);
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

    int userEmail_id = 0;

    if (retcode == SQL_SUCCESS)
    {
        retcode = SQLFetch(sqlStmtHandle);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
        {
            cout << "Error reading query!\n";
            Logger("{Users.cpp//Users::Post} Error reading query to add new user!");
            return false;
        }
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &userEmail_id, 0, &lenth);
        }
    }
    else
    {
        Logger("{Users.cpp//Users::Post} Query is failed!");
        return false;
    }

    if (userEmail_id != 0) //NEW USER ADD
    {
        string put = "INSERT INTO Users VALUES('";
        put += newObject["userNameArr"].get<string>() + "', '" +
            newObject["userSurnameArr"].get<string>() + "', '" +
            newObject["userBithday"].get<string>() + "', '" +
            newObject["userMail"].get<string>() + "', '" +
            newObject["userPassword"].get<string>() + "', " + to_string(0) + ", '" + "Novice" + "');";

        wstring wput = GetWCharFromString(put);

        if (SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS) == SQL_SUCCESS)
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
        return false;
    }
}

bool Users::Put(nlohmann::json newObject)
{
    string sTasksUpdate = "UPDATE Tasks SET ";
    sTasksUpdate += "task_Status = " + to_string(3) + ","
        "where task_Id = " + to_string(newObject["task_Id"].get<int>()) + ";";

    wstring wTasksUpdate = GetWCharFromString(sTasksUpdate);

    if (SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wTasksUpdate.c_str(), SQL_NTS) == SQL_SUCCESS)
    {
        string userRank;
        if (newObject["user_Points"].get<int>() >= 0 && newObject["user_Points"].get<int>() <= 300)
        {
            userRank = "Novice";
        }
        else if (newObject["user_Points"].get<int>() >= 301 && newObject["user_Points"].get<int>() <= 600)
        {
            userRank = "Gold";
        }
        else if (newObject["user_Points"].get<int>() >= 601 && newObject["user_Points"].get<int>() <= 900)
        {
            userRank = "Platinum";
        }
        else if (newObject["user_Points"].get<int>() >= 901 && newObject["user_Points"].get<int>() <= 1200)
        {
            userRank = "Diamomd";
        }
        else if (newObject["user_Points"].get<int>() >= 1201)
        {
            userRank = "Immortal";
        }

        string put = "UPDATE Users SET ";
        put += "user_Points = " + to_string(newObject["user_Points"].get<int>()) + "," +
            "user_Rank = '" + userRank + "' "
            "where user_Id = " + to_string(newObject["user_Id"].get<int>());

        wstring wput = GetWCharFromString(put);

        if (SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS) == SQL_SUCCESS)
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
        return false;
    }
}

bool Users::Delete(int id)
{
    string sqldelete = "Delete from Users where user_Id = ";
    sqldelete += to_string(id);

    wstring wsqldelete = GetWCharFromString(sqldelete);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);

    if (retcode == SQL_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Users::Get()
{

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM USERS", SQL_NTS);

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
                UsersStruct newUser;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newUser.userID, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newUser.userNameArr, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newUser.userSurnameArr, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newUser.userBithday, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newUser.userMail, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newUser.userPassword, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_ULONG, &newUser.userPoints, 0, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, newUser.userRank, FIELD_LEN, &lenth);

                AllUsers.emplace_back(newUser);
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

void Users::Get(int id)
{
    string put = "SELECT * FROM USERS where user_Id ='";
    put += to_string(id) + "'";
    wstring wput = GetWCharFromString(put);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

    if (retcode == SQL_SUCCESS)
    {
        retcode = SQLFetch(sqlStmtHandle);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
        {
            cout << "Error reading query!\n";
        }
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            UsersStruct newUser;
            SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newUser.userID, 0, &lenth);
            SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newUser.userNameArr, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newUser.userSurnameArr, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newUser.userBithday, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newUser.userMail, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newUser.userPassword, FIELD_LEN, &lenth);
            SQLGetData(sqlStmtHandle, 7, SQL_C_ULONG, &newUser.userPoints, 0, &lenth);
            SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, newUser.userRank, FIELD_LEN, &lenth);

            this->currentData = newUser;
        }
    }
    else
    {
        cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}
