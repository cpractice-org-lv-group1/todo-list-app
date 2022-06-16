#pragma once
#include "nlohmann/json.hpp"

class iCrudOperations
{
public:
	virtual void Get() = 0;
	virtual void Put(nlohmann::json newObject) = 0;
};

