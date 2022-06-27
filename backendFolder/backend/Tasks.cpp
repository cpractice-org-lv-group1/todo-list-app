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
        string sCategoryName((const char*)x.taskCategories_Name);
        if (sCategoryName == newObject["task_Category"].get<string>())
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
        string sStatusName((const char*)x.task_status_Name);
        if (sStatusName == newObject["task_Status"].get<string>())
        {
            statusId = x.task_status_Id;
        }
    }
    return statusId;
}

bool Tasks::Put(nlohmann::json newObject)
{
    string put = "UPDATE Tasks SET ";
    put += "task_Header = '" + newObject["task_Header"].get<string>() + "'," +
           "task_Body = '" + newObject["task_Body"].get<string>() + "'," +
            "task_Start_Time = '" + newObject["task_Start_Time"].get<string>() + "'," +
            "task_Expected_End_Time = '" + newObject["task_Expected_End_Time"].get<string>() + "'," +
            "task_Real_End_Time = '" + newObject["task_Real_End_Time"].get<string>() + "'," +
            "task_Status = " + to_string(takeTaskStatusId_FromString(newObject)) + "," +
            "task_Difficulty = " + to_string(newObject["task_Difficulty"].get<int>()) +
            "where task_Id = " + to_string(newObject["task_Id"].get<int>());

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

void Tasks::Delete(int id)
{
    string sqldelete = "Delete from Tasks where task_Id = ";
    sqldelete += to_string(id);

    wstring wsqldelete = GetWCharFromString(sqldelete);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
}

vector<Tasks::TasksStruct> Tasks::GetData()
{
    return CurrentTasks;
}

void Tasks::Get()
{

}

bool Tasks::Post(nlohmann::json newObject)
{
    string put = "INSERT INTO Tasks VALUES('";
    put += newObject["task_Header"].get<string>() + "', '" +
        newObject["task_Body"].get<string>() + "', '" +
        newObject["task_Start_Time"].get<string>() + "', '" +
        newObject["task_Expected_End_Time"].get<string>() + "'," +
        newObject["task_Real_End_Time"].get<string>() + "," + 
        to_string(takeTaskStatusId_FromString(newObject)) + "," +
        to_string(takeCategoryId_FromString(newObject)) + "," +
        to_string(newObject["task_User"].get<int>()) + "," +
        to_string(newObject["task_Difficulty"].get<int>()) + ");";

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

void Tasks::Get(int id)
{
    string put = "SELECT t.task_Id, t.task_Header, t.task_Body, t.task_Start_Time,\
        t.task_Expected_End_Time, t.task_Real_End_Time, ts.task_status_Name, tc.taskCategories_Name, t.task_User, task_Difficulty\
        FROM Tasks t\
        left join TaskCategories tc on tc.taskCategories_Id = t.task_Category\
        left join TaskStatuses ts on t.task_Status = ts.task_status_Id\
    where task_User = ";
    put += to_string(id);
    wstring wput = GetWCharFromString(put);
    CurrentTasks.clear();

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
                    string none = "None";
                    newTask.task_Real_End_Time[0] = none[0];
                    newTask.task_Real_End_Time[1] = none[1];
                    newTask.task_Real_End_Time[2] = none[2];
                    newTask.task_Real_End_Time[3] = none[3];
                    newTask.task_Real_End_Time[4] = '\0';
                }
                cout << newTask.JSON().dump() << endl;
                CurrentTasks.emplace_back(newTask);
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


