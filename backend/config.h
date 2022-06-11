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
const int SQL_RETURN_CODE_LEN = 1000;
const int SQL_RESULT_LEN = 240;
__declspec(selectany)SQLHANDLE sqlConnHandle;
__declspec(selectany)SQLHANDLE sqlStmtHandle;
__declspec(selectany)SQLHANDLE sqlEnvHandle;
__declspec(selectany)SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
__declspec(selectany)SQLRETURN retcode;
__declspec(selectany)SQLLEN lenth;
