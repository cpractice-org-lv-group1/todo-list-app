#pragma once
#include "iCrudOperations.h"
#include "config.h"
#define FIELD_LEN 50

class FriendStatuses : public iCrudOperations
{
    struct FriendStatusesStruct
    {
        SQLINTEGER friend_status_Id;
        SQLCHAR  friend_status_Name[FIELD_LEN];
        SQLCHAR  friend_status_Description[FIELD_LEN];

        void Print() const
        {
            std::cout << this->friend_status_Id << "\t" << this->friend_status_Name << "\t" << this->friend_status_Description;
            std::cout << std::endl;
        }
    };
    std::vector<FriendStatusesStruct> AllFriendStatuses;
public:
    void Get() override;
    void Get(int id) override {};
    bool Post(const nlohmann::json& newObject) override;
    bool Put(const nlohmann::json &newObject) override { return true; };
    bool Delete(int id) override;
    std::vector<FriendStatusesStruct> GetData() const;
};





