#include "TaskStatuses.h"

bool TaskStatuses::Delete(int id)
{
    std::string sqldelete = "Delete from TaskStatuses where task_status_Id = ";
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

std::vector<TaskStatuses::TaskStatusesStruct> TaskStatuses::GetData() const
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
                std::cout << "Error reading query!\n";
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
        std::cout << "Error getting data!";
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

bool TaskStatuses::Post(const nlohmann::json& newObject)
{
    std::string put = "INSERT INTO TaskStatuses VALUES('";
    put += newObject["task_status_Name"].get<std::string>() + "', '" +
        newObject["task_status_Description"].get<std::string>() + "'," + ");";

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
