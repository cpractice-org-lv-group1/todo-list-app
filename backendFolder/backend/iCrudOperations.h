#pragma once
#include "nlohmann/json.hpp"

class iCrudOperations
{
public:
	virtual void Get() = 0;
	virtual bool Post(nlohmann::json newObject) = 0;
	virtual bool Put(nlohmann::json newObject) = 0;
	virtual void Delete(int id) = 0;
};

