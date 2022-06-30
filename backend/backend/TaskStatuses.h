#pragma once
#include "iCrudOperations.h"
#include "config.h"
#define FIELD_LEN 50

class TaskStatuses : public iCrudOperations
{
    struct TaskStatusesStruct
    {
        SQLINTEGER task_status_Id;
        SQLCHAR  task_status_Name[FIELD_LEN];
        SQLCHAR  task_status_Description[FIELD_LEN];

        void Print() const
        {
            std::cout << this->task_status_Id << "\t" << this->task_status_Name << "\t" << this->task_status_Description;
            std::cout << std::endl;
        }
    };
    std::vector<TaskStatusesStruct> AllTaskStatuses;
public:
    void Get() override;
    void Get(int id) override {};
    bool Post(const nlohmann::json& newObject) override;
    bool Put(const nlohmann::json &newObject) override { return true; };
    bool Delete(int id) override;
    std::vector<TaskStatusesStruct> GetData() const;
};




