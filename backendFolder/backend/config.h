#pragma once
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <algorithm>
#include <sql.h>
#include <sqlext.h>
#include "WSA_loader.h"
#include "Server.h"

const int SQL_RETURN_CODE_LEN = 1000;
const int SQL_RESULT_LEN = 240;
__declspec(selectany)SQLHANDLE sqlConnHandle;
__declspec(selectany)SQLHANDLE sqlStmtHandle;
__declspec(selectany)SQLHANDLE sqlEnvHandle;
__declspec(selectany)SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
__declspec(selectany)SQLRETURN retcode;
__declspec(selectany)SQLLEN lenth;

//static const int MAX_CLIENTS = 10;

inline wchar_t* GetWCharFromString(std::string inString)
{
    std::wstring wsinString(inString.begin(), inString.end());
    unsigned int maxlength = inString.length() + 1;
    int len = wcsnlen_s(wsinString.c_str(), maxlength);
    wchar_t* outString = new wchar_t[len + 1];

    wcscpy_s(outString, len + 1, wsinString.c_str());

    return outString;
}


inline void completedConnections()
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

    std::cout << "\nPress any key to exit...";
    getchar();
}

// //initializations
   // sqlConnHandle = NULL;
   // sqlStmtHandle = NULL;


   // //allocations
   // if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
   //     completedConnections();

   // if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
   //     completedConnections();

   // if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
   //     completedConnections();

   // //output
   // cout << "Attempting connection to SQL Server...";
   // cout << "\n";

   // switch (SQLDriverConnect(sqlConnHandle,
   //     NULL,
   //     (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=mnkserver.database.windows.net, 1433;DATABASE=TodolistDB;UID=sanyok;PWD=!Politech;",
   //     SQL_NTS,
   //     retconstring,
   //     1024,
   //     NULL,
   //     SQL_DRIVER_NOPROMPT)) {

   // case SQL_SUCCESS:
   //     cout << "Successfully connected to SQL Server";
   //     cout << "\n";
   //     break;

   // case SQL_SUCCESS_WITH_INFO:
   //     cout << "Successfully connected to SQL Server";
   //     cout << "\n";
   //     break;

   // case SQL_INVALID_HANDLE:
   //     cout << "Could not connect to SQL Server";
   //     cout << "\n";
   //     completedConnections();

   // case SQL_ERROR:
   //     cout << "Could not connect to SQL Server";
   //     cout << "\n";
   //     completedConnections();

   // default:
   //     break;
   // }

   // //if there is a problem connecting then exit application
   // if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
   //     completedConnections();

   // //output
   // cout << "\n";
   // cout << "Executing query...";
   // cout << "\n";


   // //USERS
   // auto result = CRUD::Get<Users>().GetData();

   //for_each(result.begin(), result.end(), [](auto x) {
   //    x.Print();
   //    });
   //cout << "\n";

   // //TASKS
   //auto result2 = CRUD::Get<Tasks>().GetData();
   // for_each(result2.begin(), result2.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //TASK Statuses
   // auto result3 = CRUD::Get<TaskStatuses>().GetData();
   // for_each(result3.begin(), result3.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //Friendships
   // auto result4 = CRUD::Get<Friendships>().GetData();
   // for_each(result4.begin(), result4.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //Friendship statuses
   // auto result5 = CRUD::Get<FriendStatuses>().GetData();
   // for_each(result5.begin(), result5.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //TASKS Categories
   // auto result6 = CRUD::Get<TaskCategories>().GetData();
   // for_each(result6.begin(), result6.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";
