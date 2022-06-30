#include "TaskCategories.h"

bool TaskCategories::Put(const nlohmann::json &newObject)
{
    std::string put = "UPDATE TaskCategories SET ";
    put += "taskCategories_Name = '" + newObject["taskCategories_Name"].get<std::string>() + "'\
    where taskCategories_Id = " + std::to_string(newObject["taskCategories_Id"].get<int>());

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

bool TaskCategories::Delete(int id)
{
    std::string put = "UPDATE Tasks SET ";
    put += "task_Category = 1\
    where task_Category = " + std::to_string(id);
    std::wstring wput = GetWCharFromString(put);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);
    std::cout << retcode << std::endl;

    
    std::string sqldelete = "Delete from TaskCategories where taskCategories_Id = ";
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

std::vector<TaskCategories::TaskCategoriesStruct> TaskCategories::GetData() const
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
                std::cout << "Error reading query!\n";
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
        std::cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

void TaskCategories::Get(int userId)
{
    std::string put = "select * from TaskCategories where taskCategories_User IS NULL or taskCategories_User = ";
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
                TaskCategoriesStruct newTaskCategorie;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTaskCategorie.taskCategories_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTaskCategorie.taskCategories_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_ULONG, &newTaskCategorie.taskCategories_User, 0, &lenth);

                int value = newTaskCategorie.taskCategories_User;
                if(value < 0)
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
        std::cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

bool TaskCategories::Post(const nlohmann::json& newObject)
{
    std::string put = "INSERT INTO TaskCategories VALUES('";
    put += newObject["taskCategories_Name"].get<std::string>() + "', " +
        std::to_string(newObject["taskCategories_User"].get<int>()) + ");";

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
