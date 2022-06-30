#pragma once
#include "iCrudOperations.h"
#include "config.h"
#define FIELD_LEN 50

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

        void Print() const
        {
            std::cout << this->friendship_Id << "\t" << this->friendship_RequesterId << "\t" << this->friendship_AdresserId
                << "\t" << this->friendship_RequestTime << "\t" << this->friendship_ResponceTime << "\t" << this->friendship_Status;
            std::cout << std::endl;
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
        SQLCHAR friendship_ResponceTime[FIELD_LEN];
        SQLINTEGER friendship_Id;

        void Print() const
        {
            std::cout << this->user_Id << "\t" << this->user_Name << "\t" << this->user_Surname
                << "\t" << this->user_Birthday << "\t" << this->user_Mail << "\t" << this->user_Points << "\t" 
                << this->user_Rank << "\t" << this->friend_status_Name<<"\t"<<this->friendship_ResponceTime<<"\t" << this->friendship_Id;
            std::cout << std::endl;
        }

        nlohmann::json JSON() const
        {
            std::string user_Name2((const char*)user_Name);
            std::string user_Surname2((const char*)user_Surname);
            std::string user_Birthday2((const char*)user_Birthday);
            std::string user_Mail2((const char*)user_Mail);
            std::string user_Rank2((const char*)user_Rank);
            std::string friend_status_Name2((const char*)friend_status_Name);
            std::string friendship_ResponceTime2((const char*)friendship_ResponceTime);

            auto myJSON = nlohmann::json{ {"user_Id", user_Id},
                                                    {"user_Name", user_Name2},
                                                    {"user_Surname", user_Surname2},
                                                    {"user_Birthday", user_Birthday2},
                                                    {"user_Mail", user_Mail2},
                                                    {"user_Points", user_Points},
                                                    {"user_Rank", user_Rank2},
                                                    {"friend_status_Name", friend_status_Name2},
                                                    {"friendship_ResponceTime", friendship_ResponceTime2},
                                                    {"friendship_Id", friendship_Id} };
            return myJSON;
        }
    };

    std::vector<FriendshipsStruct> AllFriendships;
    std::vector<FriendStruct> AllFriends;
public:
    void Get() override;
    void Get(int userId) override;
    bool Post(const nlohmann::json& newObject) override;
    bool Put(const nlohmann::json &newObject) override;
    bool Delete(int id) override;
    bool checkAlreadyFriend(int friendship_RequesterId, int addresserId);
    std::vector<FriendshipsStruct> GetData() const;
    std::vector<FriendStruct> GetAllFriends() const;
};



