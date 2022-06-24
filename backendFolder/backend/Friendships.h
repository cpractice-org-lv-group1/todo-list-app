#pragma once
#include "iCrudOperations.h"
#include "config.h"
#define FIELD_LEN 50

using namespace std;

class Friendships : public iCrudOperations
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
    struct FriendStruct
    {
        SQLINTEGER user_Id;
        SQLCHAR user_Name[FIELD_LEN];
        SQLCHAR user_Surname[FIELD_LEN];
        SQLCHAR user_Birthday[FIELD_LEN];
        SQLCHAR user_Mail[FIELD_LEN];
        SQLINTEGER user_Points;
        SQLCHAR user_Rank[FIELD_LEN];
        SQLCHAR friend_status_Name[FIELD_LEN];

        void Print()
        {
            cout << this->user_Id << "\t" << this->user_Name << "\t" << this->user_Surname
                << "\t" << this->user_Birthday << "\t" << this->user_Mail << "\t" << this->user_Points << "\t" 
                << this->user_Rank << "\t" << this->friend_status_Name;
            cout << endl;
        }
        string JSON()
        {
            std::stringstream stream;
            std::string JSON_string = "";

            stream << JSON_string << "{\"user_Id\":" << user_Id << "," <<
                "\"user_Name\":" << "\"" << user_Name << "\"," <<
                "\"user_Surname\":" << "\"" << user_Surname << "\"," <<
                "\"user_Birthday\":" << "\"" << user_Birthday << "\"," <<
                "\"user_Mail\":" << "\"" << user_Mail << "\"," <<
                "\"user_Points\":" << user_Points << "," <<
                "\"user_Rank\":" << "\"" << user_Rank << "\"," <<
                "\"user_Birthday\":" << "\"" << friend_status_Name << "\"}";
            stream >> JSON_string;
            return JSON_string;
        }
    };

    vector<FriendshipsStruct> AllFriendships;
    vector<FriendStruct> AllFriends;
public:
    void Get();
    void Get(int userId);
    bool Put(nlohmann::json newObject) { return true; };
    void Delete(int id);
    vector<FriendshipsStruct> GetData();
    vector<FriendStruct> GetAllFriends();
};



