#pragma once
#include <string>
#include "EnumTables.h"
#include "Users.h"
#include "Tasks.h"
#include "TaskCategories.h"
#include "FriendStatuses.h"
#include "Friendships.h"
#include "TaskStatuses.h"
#include <any>

EnumTables resolveTables(std::string input) {
	if (input == "Users") return EnumTables::Users_dbo;
	if (input == "TaskStatuses") return EnumTables::TaskStatuses_dbo;
	if (input == "Frienships") return EnumTables::Frienships_dbo;
	if (input == "FriendStatuses") return EnumTables::FriendStatuses_dbo;
	if (input == "TaskCategories") return EnumTables::TaskCategories_dbo;
	if (input == "Tasks") return EnumTables::Tasks_dbo;
	return EnumTables::UNKNOWN;
}

static class CRUD {
	
public:
	static any Get(std::string tableName) {
		Users users_dbo;
		TaskStatuses taskstatuses_dbo;
		TaskStatuses taskStatuses_dbo;
		Friendships frienships_dbo;
		FriendStatuses friendStatuses_dbo;
		Tasks tasks_dbo;
		TaskCategories taskCategories_dbo;

		switch (resolveTables(tableName))
		{
		case EnumTables::Users_dbo:
		    users_dbo.Get();
			return users_dbo;
			break;
		case EnumTables::TaskStatuses_dbo:
			taskstatuses_dbo.Get();
			return taskStatuses_dbo;
			break;
		default:
			break;
		}
	}
};