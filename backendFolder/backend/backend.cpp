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

using namespace std;

int main() 
{
	mINI::INIFile file("cfg.ini");
	mINI::INIStructure ini;
	file.read(ini);

	WSA_loader::Load();
	Server my_server(ini);
	puts("Start server... DONE.");
	Logger("Server Started. Waiting for incoming connections...");
	my_server.RunSERVER();
	WSA_loader::Clean();

    return 0;
}