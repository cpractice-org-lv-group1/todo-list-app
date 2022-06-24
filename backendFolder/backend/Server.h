#pragma once
#include "clientSocket.h"
#include "serverSocket.h"
#include <string>
#include <iostream>
#include <mini/ini.h>

class Server
{
	clientSocket client_socket;
	serverSocket server_socket;
	mINI::INIStructure iniCFG;
public:
	Server(mINI::INIStructure myINI);
	void Initiliaze();
	void RunSERVER();
	void SendMSG(std::string MESSAGE, int SocketNum);
};

