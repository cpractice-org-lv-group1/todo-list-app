#include "Tasks.h"

vector<Tasks::TasksStruct> Tasks::GetData()
{
    return AllTasks;
}


void Tasks::Get()
{
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Tasks", SQL_NTS);

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
                TasksStruct newTask;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTask.task_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTask.task_Header, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newTask.task_Body, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_ULONG, newTask.task_Start_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newTask.task_Expected_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newTask.task_Real_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_CHAR, &newTask.task_Status, 0, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, &newTask.task_Category, 0, &lenth);
                SQLGetData(sqlStmtHandle, 9, SQL_C_CHAR, &newTask.task_User, 0, &lenth);
                SQLGetData(sqlStmtHandle, 10, SQL_C_ULONG, &newTask.task_Difficulty, 0, &lenth);

                AllTasks.emplace_back(newTask);
            }
            else break;
        }
    }
    else
    {
        cout << "Error getting data!";
    }
}