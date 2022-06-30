#include "Tasks.h"
#include "CRUD.h"
#include "TaskStatuses.h"
#include "TaskCategories.h"


int Tasks::takeCategoryId_FromString(nlohmann::json newObject)
{
    auto taskCategories = CRUD::Get<TaskCategories>().GetData();
    int categoryId = 0;

    for (const auto& x : taskCategories)
    {
        std::string sCategoryName((const char*)x.taskCategories_Name);
        if (sCategoryName == newObject["task_Category"].get<std::string>())
        {
            categoryId = x.taskCategories_Id;
        }
    }
    return categoryId;
}

int Tasks::takeTaskStatusId_FromString(nlohmann::json newObject)
{
    auto taskStatuses = CRUD::Get<TaskStatuses>().GetData();
    int statusId = 0;

    for (const auto& x : taskStatuses)
    {
        std::string sStatusName((const char*)x.task_status_Name);
        if (sStatusName == newObject["task_Status"].get<std::string>())
        {
            statusId = x.task_status_Id;
        }
    }
    return statusId;
}

bool Tasks::Put(const nlohmann::json &newObject)
{
    std::string put = "UPDATE Tasks SET ";
    put += "task_Header = '" + newObject["task_Header"].get<std::string>() + "'," +
           "task_Body = '" + newObject["task_Body"].get<std::string>() + "'," +
            "task_Start_Time = '" + newObject["task_Start_Time"].get<std::string>() + "'," +
            "task_Expected_End_Time = '" + newObject["task_Expected_End_Time"].get<std::string>() + "'," +
            "task_Difficulty = " + std::to_string(newObject["task_Difficulty"].get<int>()) +","+
            "task_Category = " + std::to_string(takeCategoryId_FromString(newObject)) + " " +
            "where task_Id = " + std::to_string(newObject["task_Id"].get<int>())+";";

    std::wstring wput = GetWCharFromString(put);

    if (SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS) == SQL_SUCCESS)
    {
        return true;
    }
    else
    {
        Logger("{Tasks.cpp//Tasks::Post} Error Put Tasks!");
        return false;
    }
}

bool Tasks::Delete(int id)
{
    std::string sTasksUpdate = "UPDATE Tasks SET ";
    sTasksUpdate += "task_Status = " + std::to_string(4) +
        "where task_Id = " + std::to_string(id) + ";";

    std::wstring wTasksUpdate = GetWCharFromString(sTasksUpdate);

    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wTasksUpdate.c_str(), SQL_NTS);

    if (retcode == SQL_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<Tasks::TasksStruct> Tasks::GetData() const
{
    return CurrentTasks;
}

std::vector<Tasks::TasksStruct> Tasks::GetAllNotStartedTasks() const
{
    return AllNotStartedTasks;
}

void Tasks::Get()
{
    std::string put = "SELECT t.task_Id, t.task_Header, t.task_Body, t.task_Start_Time,\
        t.task_Expected_End_Time, t.task_Real_End_Time, ts.task_status_Name, tc.taskCategories_Name, t.task_User, task_Difficulty\
        FROM Tasks t\
        left join TaskCategories tc on tc.taskCategories_Id = t.task_Category\
        left join TaskStatuses ts on t.task_Status = ts.task_status_Id where t.task_Status = 1";
    std::wstring wput = GetWCharFromString(put);
    AllNotStartedTasks.clear();

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
                TasksStruct newTask = {};

                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTask.task_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTask.task_Header, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newTask.task_Body, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newTask.task_Start_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newTask.task_Expected_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newTask.task_Real_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_CHAR, newTask.task_Status, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, newTask.task_Category, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 9, SQL_C_ULONG, &newTask.task_User, 0, &lenth);
                SQLGetData(sqlStmtHandle, 10, SQL_C_ULONG, &newTask.task_Difficulty, 0, &lenth);

                auto first = newTask.task_Real_End_Time[0];
                if (!isdigit(first))
                {
                    std::string none = "None";
                    newTask.task_Real_End_Time[0] = none[0];
                    newTask.task_Real_End_Time[1] = none[1];
                    newTask.task_Real_End_Time[2] = none[2];
                    newTask.task_Real_End_Time[3] = none[3];
                    newTask.task_Real_End_Time[4] = '\0';
                }
                AllNotStartedTasks.emplace_back(newTask);
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

bool Tasks::Post(const nlohmann::json& newObject)
{
    std::string put = "INSERT INTO Tasks VALUES('";
    put += newObject["task_Header"].get<std::string>() + "', '" +
        newObject["task_Body"].get<std::string>() + "', '" +
        newObject["task_Start_Time"].get<std::string>() + "', '" +
        newObject["task_Expected_End_Time"].get<std::string>() + "'," +
        newObject["task_Real_End_Time"].get<std::string>() + "," +
        std::to_string(takeTaskStatusId_FromString(newObject)) + "," +
        std::to_string(takeCategoryId_FromString(newObject)) + "," +
        std::to_string(newObject["task_User"].get<int>()) + "," +
        std::to_string(newObject["task_Difficulty"].get<int>()) + ");";

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

void Tasks::Get(int id)
{
    std::string put = "SELECT t.task_Id, t.task_Header, t.task_Body, t.task_Start_Time,\
        t.task_Expected_End_Time, t.task_Real_End_Time, ts.task_status_Name, tc.taskCategories_Name, t.task_User, task_Difficulty\
        FROM Tasks t\
        left join TaskCategories tc on tc.taskCategories_Id = t.task_Category\
        left join TaskStatuses ts on t.task_Status = ts.task_status_Id\
    where task_User = ";
    put += std::to_string(id);
    std::wstring wput = GetWCharFromString(put);
    CurrentTasks.clear();

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
                TasksStruct newTask = {};

                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTask.task_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTask.task_Header, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newTask.task_Body, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newTask.task_Start_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newTask.task_Expected_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newTask.task_Real_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_CHAR, newTask.task_Status, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, newTask.task_Category, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 9, SQL_C_ULONG, &newTask.task_User, 0, &lenth);
                SQLGetData(sqlStmtHandle, 10, SQL_C_ULONG, &newTask.task_Difficulty, 0, &lenth);

                auto first = newTask.task_Real_End_Time[0];
                if (!isdigit(first))
                {
                    std::string none = "None";
                    newTask.task_Real_End_Time[0] = none[0];
                    newTask.task_Real_End_Time[1] = none[1];
                    newTask.task_Real_End_Time[2] = none[2];
                    newTask.task_Real_End_Time[3] = none[3];
                    newTask.task_Real_End_Time[4] = '\0';
                }
                CurrentTasks.emplace_back(newTask);
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


