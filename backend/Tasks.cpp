#include "Tasks.h"

vector<Tasks::TasksStruct> Tasks::GetData()
{
    return CurrentTasks;
}


void Tasks::Get()
{

}

void Tasks::Get(int id)
{
    string put = "SELECT * FROM Tasks where task_User =";
    put += to_string(id);
    wstring wput = GetWCharFromString(put);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);

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
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newTask.task_Start_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newTask.task_Expected_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newTask.task_Real_End_Time, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_ULONG, &newTask.task_Status, 0, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_ULONG, &newTask.task_Category, 0, &lenth);
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


