#pragma once
#include "nlohmann/json.hpp"

class iCrudOperations
{
public:
	virtual void Get() = 0;
	virtual void Get(int Id) = 0;
	virtual bool Post(const nlohmann::json& newObject) = 0;
	virtual bool Put(const nlohmann::json &newObject) = 0;
	virtual bool Delete(int id) = 0;
};

