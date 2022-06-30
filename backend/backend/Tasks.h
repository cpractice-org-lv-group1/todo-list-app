#pragma once
#include "iCrudOperations.h"
#include "config.h"
#include <nlohmann/json.hpp>

#define FIELD_LEN 50

class Tasks : public iCrudOperations
{
    struct TasksStruct
    {
        SQLINTEGER task_Id;
        SQLCHAR  task_Header[FIELD_LEN];
        SQLCHAR task_Body[FIELD_LEN];
        SQLCHAR task_Start_Time[FIELD_LEN];
        SQLCHAR task_Expected_End_Time[FIELD_LEN];
        SQLCHAR task_Real_End_Time[FIELD_LEN];
        SQLCHAR task_Status[FIELD_LEN];
        SQLCHAR task_Category[FIELD_LEN];
        SQLINTEGER task_User;
        SQLINTEGER task_Difficulty;
        
        void Print() const
        {
            std::cout << this->task_Id << "\t" << this->task_Header << "\t" << this->task_Body
                << "\t" << this->task_Start_Time << "\t" << this->task_Expected_End_Time << "\t" << this->task_Real_End_Time
                << "\t" << this->task_Status << "\t" << this->task_Category << "\t" << this->task_User << "\t" << this->task_Difficulty;
            std::cout << std::endl;
        }

        nlohmann::json JSON()
        {
            std::string task_Header2((const char*)task_Header);
            std::string task_Body2((const char*)task_Body);
            std::string task_Start_Time2((const char*)task_Start_Time);
            std::string task_Expected_End_Time2((const char*)task_Expected_End_Time);
            std::string task_Real_End_Time2((const char*)task_Real_End_Time);
            std::string task_Status2((const char*)task_Status);
            std::string task_Category2((const char*)task_Category);

            auto myJSON = nlohmann::json{ {"task_Id", task_Id},
                                                    {"task_Header", task_Header2},
                                                    {"task_Body", task_Body2},
                                                    {"task_Start_Time", task_Start_Time2},
                                                    {"task_Expected_End_Time", task_Expected_End_Time2},
                                                    {"task_Real_End_Time", task_Real_End_Time2},
                                                    {"task_Status", task_Status2},
                                                    {"task_Category", task_Category2},
                                                    {"task_User", task_User},
                                                    {"task_Difficulty", task_Difficulty}};
            return myJSON;
        }
    };
    std::vector<TasksStruct> CurrentTasks;
    std::vector<TasksStruct>AllNotStartedTasks;
public:
    void Get(int id) override;
    void Get() override; //NotStarted Tasks
    bool Post(const nlohmann::json& newObject) override;
    bool Put(const nlohmann::json& newObject) override;
    bool Delete(int id) override;
    std::vector<TasksStruct> GetData() const;
    std::vector<TasksStruct> GetAllNotStartedTasks() const;
    int takeCategoryId_FromString(nlohmann::json newObject);
    int takeTaskStatusId_FromString(nlohmann::json newObject);
};




