#pragma once
#include "iCrudOperations.h"
#include "config.h"
#include <sstream>
#define FIELD_LEN 50

using namespace std;

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

        string JSON()
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
    vector<UsersStruct> AllUsers;
    UsersStruct currentUser;
    UsersStruct currentData;
public: 
    void Get() override;
    void Get(int id) override;
    void Get(string email);
    bool Post(nlohmann::json newObject) override;
    bool Put(nlohmann::json newObject) override { return true; };
    bool Delete(int id) override;
    vector<UsersStruct> GetData();
    UsersStruct GetCurrentUser();
    UsersStruct GetCurrentData();
};

