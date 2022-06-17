#include "TaskCategories.h"

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