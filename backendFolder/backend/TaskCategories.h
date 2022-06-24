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
        string JSON()
        {
            std::stringstream stream;
            std::string JSON_string = "";

            stream << JSON_string << "{\"taskCategories_Id\":" << taskCategories_Id << "," <<
                "\"taskCategories_Name\":" << "\"" << taskCategories_Name << "\"," <<
                "\"taskCategories_User\":" << taskCategories_User << "}";
            stream >> JSON_string;
            return JSON_string;
        }
    };
    vector<TaskCategoriesStruct> AllTaskCategories;
public:
    void Get();
    void Get(int userId);
    bool Put(nlohmann::json newObject) { return true; };
    void Delete(int id);
    vector<TaskCategoriesStruct> GetData();
};





