#pragma once
#include "iCrudOperations.h"
#include "config.h"
#define FIELD_LEN 50

using namespace std;

class FriendStatuses : public iCrudOperations
{
    struct FriendStatusesStruct
    {
        SQLINTEGER friend_status_Id;
        SQLCHAR  friend_status_Name[FIELD_LEN];
        SQLCHAR  friend_status_Description[FIELD_LEN];

        void Print()
        {
            cout << this->friend_status_Id << "\t" << this->friend_status_Name << "\t" << this->friend_status_Description;
            cout << endl;
        }
    };
    vector<FriendStatusesStruct> AllFriendStatuses;
public:
    void Get();
    vector<FriendStatusesStruct> GetData();
};





