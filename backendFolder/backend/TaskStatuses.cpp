#include "TaskStatuses.h"

vector<TaskStatuses::TaskStatusesStruct> TaskStatuses::GetData()
{
    return AllTaskStatuses;
}


void TaskStatuses::Get()
{
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM TaskStatuses", SQL_NTS);

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
                TaskStatusesStruct newTaskStatus;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newTaskStatus.task_status_Id, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newTaskStatus.task_status_Name, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newTaskStatus.task_status_Description, FIELD_LEN, &lenth);

                AllTaskStatuses.emplace_back(newTaskStatus);
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
