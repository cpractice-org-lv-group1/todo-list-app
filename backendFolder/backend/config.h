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
#include <mini/ini.h>

__declspec(selectany)SQLHANDLE sqlConnHandle;
__declspec(selectany)SQLHANDLE sqlStmtHandle;
__declspec(selectany)SQLHANDLE sqlEnvHandle;
__declspec(selectany)SQLWCHAR retconstring[1000];
__declspec(selectany)SQLRETURN retcode;
__declspec(selectany)SQLLEN lenth;


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
