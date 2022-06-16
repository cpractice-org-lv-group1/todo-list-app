#pragma once
#include "iCrudOperations.h"
#include "config.h"

#define FIELD_LEN 50

using namespace std;

class TaskCategories : public iCrudOperations
{
    struct TaskCategoriesStruct
    {
        SQLINTEGER taskCategories_Id;
        SQLCHAR taskCategories_Name[FIELD_LEN];
        SQLINTEGER  taskCategories_User;

        void Print()
        {
            cout << this->taskCategories_Id << "\t" << this->taskCategories_Name << "\t" << this->taskCategories_User;
            cout << endl;
        }
    };
    vector<TaskCategoriesStruct> AllTaskCategories;
public:
    void Get();
    void Put(nlohmann::json newObject) {};
    vector<TaskCategoriesStruct> GetData();
};





