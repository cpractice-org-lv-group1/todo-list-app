#pragma once
#include "iCrudOperations.h"
#include "config.h"
#include <nlohmann/json.hpp>

#define FIELD_LEN 50

using namespace std;

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
        SQLINTEGER task_Status;
        SQLINTEGER task_Category;
        SQLINTEGER task_User;
        SQLINTEGER task_Difficulty;
        
        void Print()
        {
            cout << this->task_Id << "\t" << this->task_Header << "\t" << this->task_Body
                << "\t" << this->task_Start_Time << "\t" << this->task_Expected_End_Time << "\t" << this->task_Real_End_Time
                << "\t" << this->task_Status << "\t" << this->task_Category << "\t" << this->task_User << "\t" << this->task_Difficulty;
            cout << endl;
        }

        nlohmann::json JSON()
        {
            string task_Header2((const char*)task_Header);
            string task_Body2((const char*)task_Body);
            string task_Start_Time2((const char*)task_Start_Time);
            string task_Expected_End_Time2((const char*)task_Expected_End_Time);
            string task_Real_End_Time2((const char*)task_Real_End_Time);

            nlohmann::json myJSON = nlohmann::json{ {"task_Id", task_Id},
                                                    {"task_Header", task_Header2},
                                                    {"task_Body", task_Body2},
                                                    {"task_Start_Time", task_Start_Time2},
                                                    {"task_Expected_End_Time", task_Expected_End_Time2},
                                                    {"task_Real_End_Time", task_Real_End_Time2},
                                                    {"task_Status", task_Status},
                                                    {"task_Category", task_Category},
                                                    {"task_User", task_User},
                                                    {"task_Difficulty", task_Difficulty}};
            return myJSON;
        }
    };
    vector<TasksStruct> CurrentTasks;
public:
    void Get(int id);
    void Get();
    bool Put(nlohmann::json newObject) { return true; };
    void Delete(int id);
    vector<TasksStruct> GetData();
};




