#include "TaskCategories.h"

bool TaskCategories::Put(nlohmann::json newObject)
{
    string put = "UPDATE TaskCategories SET ";
    put += "taskCategories_Name = '" + newObject["taskCategories_Name"].get<string>() + "'\
    where taskCategories_Id = " + to_string(newObject["taskCategories_Id"].get<int>());

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

void TaskCategories::Delete(int id)
{
    string sqldelete = "Delete from TaskCategories where taskCategories_Id = ";
    sqldelete += to_string(id);

    wstring wsqldelete = GetWCharFromString(sqldelete);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
}

vector<TaskCategories::TaskCategoriesStruct> TaskCategories::GetData()
{
    return AllTaskCategories;
}


void TaskCategories::Get()
{
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM TaskCategories", SQL_NTS);

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
                TaskCategoriesStruct newTaskCategorie;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTaskCategorie.taskCategories_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTaskCategorie.taskCategories_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_ULONG, &newTaskCategorie.taskCategories_User, 0, &lenth);

                int value = newTaskCategorie.taskCategories_User;
                if (value < 0)
                {
                    newTaskCategorie.taskCategories_User = 0;
                }
                AllTaskCategories.emplace_back(newTaskCategorie);
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

void TaskCategories::Get(int userId)
{
    string put = "select * from TaskCategories where taskCategories_User IS NULL or taskCategories_User = ";
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
                TaskCategoriesStruct newTaskCategorie;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTaskCategorie.taskCategories_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTaskCategorie.taskCategories_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_ULONG, &newTaskCategorie.taskCategories_User, 0, &lenth);

                int value = newTaskCategorie.taskCategories_User;
                if (value < 0)
                {
                    newTaskCategorie.taskCategories_User = 0;
                }
                AllTaskCategories.emplace_back(newTaskCategorie);
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
