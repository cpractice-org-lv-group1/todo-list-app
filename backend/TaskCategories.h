#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <algorithm>
#include <sql.h>
#include <sqlext.h>
#include "CrudOperations.h"
#include "Users.h"
#define FIELD_LEN 50

using namespace std;

class TaskCategories : public CrudOperations
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
    vector<TaskCategoriesStruct> GetData();
};





