#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

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
void Get();
void Put();
void Delete(int id);
void Update(string name, int id);


SQLHANDLE sqlConnHandle;
SQLHANDLE sqlStmtHandle;
SQLHANDLE sqlEnvHandle;
SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
SQLRETURN retcode;
SQLLEN lenth;

struct Users
{
    SQLINTEGER userID;
    SQLCHAR userNameArr[FIELD_LEN];
    SQLCHAR userSurnameArr[FIELD_LEN];
    SQLCHAR userBithday[FIELD_LEN];
    SQLCHAR userMail[FIELD_LEN];
    SQLCHAR userPassword[FIELD_LEN];
    SQLINTEGER userPoints;
    SQLCHAR userRank[FIELD_LEN];
};

vector<Users> AllUsers;

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

    //Put();
    //Delete(7);
    //Update("Stas", 9);
    Get();
    cout << "From NorthBackend";
    cout << "From NorthBackend2";
    cout << "Git Change";

    return 0;
}

void Get()
{
    retcode = SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM USERS", SQL_NTS);

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
                Users newUser;
                SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &newUser.userID, 0, &lenth);
                SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, newUser.userNameArr, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, newUser.userSurnameArr, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR, newUser.userBithday, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR, newUser.userMail, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR, newUser.userPassword, FIELD_LEN, &lenth);
                SQLGetData(sqlStmtHandle, 7, SQL_C_ULONG, &newUser.userPoints, 0, &lenth);
                SQLGetData(sqlStmtHandle, 8, SQL_C_CHAR, newUser.userRank, FIELD_LEN, &lenth);

                AllUsers.emplace_back(newUser);

                cout << newUser.userID << "\t" << newUser.userNameArr << "\t" << newUser.userSurnameArr
                    << "\t" << newUser.userBithday << "\t" << newUser.userMail << "\t" << newUser.userPassword
                    << "\t" << newUser.userPoints << "\t" << newUser.userRank;
                cout << endl;
            }
            else break;
        }
    }
}

void Put()
{
    string put = "INSERT INTO Users VALUES('";
    put += "Name";
    put += "', 'Surname', '2002 - 01 - 01', 'testmail@gmail.com', 'testpass', 2, 'Novice');";

    wstring wput = GetWCharFromString(put);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);
}

void Delete(int id)
{
    string sqldelete = "Delete from Users where user_Id = ";
    sqldelete += to_string(id);

    wstring wsqldelete = GetWCharFromString(sqldelete);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
}

void Update(string name, int id)
{
    string update = "update Users set user_Name = '";
    update += name;
    update += "' where user_id = ";
    update += to_string(id);

    wstring wupdate = GetWCharFromString(update);

    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wupdate.c_str(), SQL_NTS);
}