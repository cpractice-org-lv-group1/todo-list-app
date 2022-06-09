#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "CrudOperations.h"
#define FIELD_LEN 50

using namespace std;

class Users : public CrudOperations
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
    static vector<UsersStruct> AllUsers;
public: 
    void Get();
    vector<UsersStruct> GetData();
};

