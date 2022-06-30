#pragma once
#include "iCrudOperations.h"
#include "config.h"
#include <sstream>
#define FIELD_LEN 50

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

        void Print() const
        {
            std::cout << this->userID << "\t" << this->userNameArr << "\t" << this->userSurnameArr
                << "\t" << this->userBithday << "\t" << this->userMail << "\t" << this->userPassword
                << "\t" << this->userPoints << "\t" << this->userRank;
            std::cout << std::endl;
        }

        std::string JSON() const
        {
            std::stringstream stream;
            std::string JSON_string = "";

            stream << JSON_string << "{\"userID\":" << userID <<","<<
                                     "\"userNameArr\":" <<"\"" << userNameArr << "\"," <<
                                     "\"userSurnameArr\":" << "\"" << userSurnameArr << "\"," <<
                                     "\"userBithday\":" << "\"" << userBithday << "\"," <<
                                     "\"userMail\":" << "\"" << userMail << "\"," <<
                                     "\"userPassword\":" << "\"" << userPassword << "\"," <<
                                     "\"userPoints\":" << userPoints << ","<<
                                     "\"userRank\":" << "\"" << userRank << "\"" << "}";
            stream >> JSON_string;
            return JSON_string;
        }
    };
    std::vector<UsersStruct> AllUsers;
    UsersStruct currentUser;
    UsersStruct currentData;
public: 
    void Get() override;
    void Get(int id) override;
    void Get(const std::string& email);
    bool Post(const nlohmann::json& newObject) override;
    bool Put(const nlohmann::json &newObject) override;
    bool Delete(int id) override;
    std::vector<UsersStruct> GetData() const;
    UsersStruct GetCurrentUser() const;
    UsersStruct GetCurrentData() const;
};

