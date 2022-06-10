#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <algorithm>
#include <sql.h>
#include <sqlext.h>
#include "Header.h"
#include "iCrudOperations.h"
#define FIELD_LEN 50

using namespace std;

#define SQL_RETURN_CODE_LEN 1000
__declspec(selectany)SQLHANDLE sqlConnHandle;
__declspec(selectany)SQLHANDLE sqlStmtHandle;
__declspec(selectany)SQLHANDLE sqlEnvHandle;
__declspec(selectany)SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
__declspec(selectany)SQLRETURN retcode;
__declspec(selectany)SQLLEN lenth;

class Users : public iCrudOperations
{
    struct UsersStruct
    {
        SQLINTEGER userID;
        SQLCHAR userNameArr[FIELD_LEN];
        SQLCHAR userSurnameArr[FIELD_LEN];
        SQLCHAR userBithday[FIELD_LEN];
        SQLCHAR userMail[FIELD_LEN];
        SQLCHAR userPassword[FIELD_LEN];
        SQLINTEGER userPoints;
        SQLCHAR userRank[FIELD_LEN];

        void Print()
        {
            cout << this->userID << "\t" << this->userNameArr << "\t" << this->userSurnameArr
                << "\t" << this->userBithday << "\t" << this->userMail << "\t" << this->userPassword
                << "\t" << this->userPoints << "\t" << this->userRank;
            cout << endl;
        }
    };
    vector<UsersStruct> AllUsers;
public: 
    void Get();
    vector<UsersStruct> GetData();
};

