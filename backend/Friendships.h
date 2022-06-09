#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <algorithm>
#include <sql.h>
#include <sqlext.h>
#include "CrudOperations.h"
#include "Users.h"
#define FIELD_LEN 50

using namespace std;

class Friendships : public CrudOperations
{
    struct FriendshipsStruct
    {
        SQLINTEGER friendship_Id;
        SQLINTEGER friendship_RequesterId;
        SQLINTEGER friendship_AdresserId;
        SQLCHAR friendship_RequestTime[FIELD_LEN];
        SQLCHAR friendship_ResponceTime[FIELD_LEN];
        SQLINTEGER friendship_Status;

        void Print()
        {
            cout << this->friendship_Id << "\t" << this->friendship_RequesterId << "\t" << this->friendship_AdresserId
                << "\t" << this->friendship_RequestTime << "\t" << this->friendship_ResponceTime << "\t" << this->friendship_Status;
            cout << endl;
        }
    };
    vector<FriendshipsStruct> AllFriendships;
public:
    void Get();
    vector<FriendshipsStruct> GetData();
};



