#pragma once
#include "iCrudOperations.h"
#include "config.h"
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
    };
    vector<TasksStruct> AllTasks;
public:
    void Get();
    vector<TasksStruct> GetData();
};




