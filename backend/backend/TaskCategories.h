#pragma once
#include "iCrudOperations.h"
#include "config.h"

#define FIELD_LEN 50

class TaskCategories : public iCrudOperations
{
    struct TaskCategoriesStruct
    {
        SQLINTEGER taskCategories_Id;
        SQLCHAR taskCategories_Name[FIELD_LEN];
        SQLINTEGER  taskCategories_User;

        void Print()
        {
            std::cout << this->taskCategories_Id << "\t" << this->taskCategories_Name << "\t" << this->taskCategories_User;
            std::cout << std::endl;
        }
        std::string JSON()
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
    std::vector<TaskCategoriesStruct> AllTaskCategories;
public:
    void Get() override;
    void Get(int userId) override;
    bool Post(const nlohmann::json& newObject) override;
    bool Put(const nlohmann::json &newObject) override;
    bool Delete(int id) override;
    std::vector<TaskCategoriesStruct> GetData() const;
};





