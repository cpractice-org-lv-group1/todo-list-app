#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

class CrudOperations
{
public:
	virtual void Get() = 0;
};

