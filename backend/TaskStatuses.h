#pragma once
#include "iCrudOperations.h"
#include "config.h"
#define FIELD_LEN 50

using namespace std;

class TaskStatuses : public iCrudOperations
{
    struct TaskStatusesStruct
    {
        SQLINTEGER task_status_Id;
        SQLCHAR  task_status_Name[FIELD_LEN];
        SQLCHAR  task_status_Description[FIELD_LEN];

        void Print()
        {
            cout << this->task_status_Id << "\t" << this->task_status_Name << "\t" << this->task_status_Description;
            cout << endl;
        }
    };
    vector<TaskStatusesStruct> AllTaskStatuses;
public:
    void Get();
    vector<TaskStatusesStruct> GetData();
};




