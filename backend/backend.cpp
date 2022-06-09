#include "Users.h"
#include "TaskStatuses.h"
#include "Tasks.h"
#include "TaskCategories.h"
#include "FriendStatuses.h"
#include "Friendships.h"


#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
#define FIELD_LEN 50


using namespace std;

wchar_t* GetWCharFromString(string inString) 
{
    std::wstring wsinString(inString.begin(), inString.end());
    unsigned int maxlength = inString.length() + 1;
    int len = wcsnlen_s(wsinString.c_str(), maxlength);
    wchar_t* outString = new wchar_t[len + 1];

    wcscpy_s(outString, len + 1, wsinString.c_str());

    return outString;
}

void completedConnections() 
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

    cout << "\nPress any key to exit...";
    getchar();
}




int main() 
{
    //initializations
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;


    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        completedConnections();

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        completedConnections();

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        completedConnections();

    //output
    cout << "Attempting connection to SQL Server...";
    cout << "\n";

    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=mnkserver.database.windows.net, 1433;DATABASE=TodolistDB;UID=sanyok;PWD=!Politech;",
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {

    case SQL_SUCCESS:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;

    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;

    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        completedConnections();

    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        completedConnections();

    default:
        break;
    }

    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        completedConnections();

    //output
    cout << "\n";
    cout << "Executing query...";
    cout << "\n";


    //USERS
    Users User;
    User.Get();
    auto result = User.GetData();
    for_each(result.begin(), result.end(), [](auto x) {
        x.Print();
        });
    cout << "\n";

    //TASKS
    Tasks Task;
    Task.Get();
    auto result2 = Task.GetData();
    for_each(result2.begin(), result2.end(), [](auto x) {
        x.Print();
        });
    cout << "\n";

    //TASK Statuses
    TaskStatuses Taskstatus;
    Taskstatus.Get();
    auto result3 = Taskstatus.GetData();
    for_each(result3.begin(), result3.end(), [](auto x) {
        x.Print();
        });
    cout << "\n";

    //Friendships 
    Friendships Fr;
    Fr.Get();
    auto result4 = Fr.GetData();
    for_each(result4.begin(), result4.end(), [](auto x) {
        x.Print();
        });
    cout << "\n";

    //Friendship statuses
    FriendStatuses Frstatus;
    Frstatus.Get();
    auto result5 = Frstatus.GetData();
    for_each(result5.begin(), result5.end(), [](auto x) {
        x.Print();
        });
    cout << "\n";

    //TASKS Categories
    TaskCategories TaskCategorie;
    TaskCategorie.Get();
    auto result6 = TaskCategorie.GetData();
    for_each(result6.begin(), result6.end(), [](auto x) {
        x.Print();
        });
    cout << "\n";

    return 0;
}





//void Put()
//{
//    string put = "INSERT INTO Users VALUES('";
//    put += "Name";
//    put += "', 'Surname', '2002 - 01 - 01', 'testmail@gmail.com', 'testpass', 2, 'Novice');";
//
//    wstring wput = GetWCharFromString(put);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);
//}
//
//void Delete(int id)
//{
//    string sqldelete = "Delete from Users where user_Id = ";
//    sqldelete += to_string(id);
//
//    wstring wsqldelete = GetWCharFromString(sqldelete);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
//}
//
//void Update(string name, int id)
//{
//    string update = "update Users set user_Name = '";
//    update += name;
//    update += "' where user_id = ";
//    update += to_string(id);
//
//    wstring wupdate = GetWCharFromString(update);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wupdate.c_str(), SQL_NTS);
//}