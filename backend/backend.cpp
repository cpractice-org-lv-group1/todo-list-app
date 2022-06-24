#include <string.h>  
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h>
#include "Users.h"
#include "TaskStatuses.h"
#include "Tasks.h"
#include "TaskCategories.h"
#include "FriendStatuses.h"
#include "Friendships.h"
#include "config.h"
#include "CRUD.h"

#define FIELD_LEN 50

using namespace std;

int main() 
{
	WSA_loader::Load();
	Server my_server;
	puts("Start server... DONE.");
	puts("Server is waiting for incoming connections...\nPlease, start one or more client-side app.");
	my_server.RunSERVER();
	WSA_loader::Clean();

    return 0;
}


//void Delete(int id)
//{
//    string sqldelete = "Delete from Users where user_Id = ";
//    sqldelete += to_string(id);
//
//    wstring wsqldelete = GetWCharFromString(sqldelete);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
//}
//
//void Update(string name, int id)
//{
//    string update = "update Users set user_Name = '";
//    update += name;
//    update += "' where user_id = ";
//    update += to_string(id);
//
//    wstring wupdate = GetWCharFromString(update);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wupdate.c_str(), SQL_NTS);
//}