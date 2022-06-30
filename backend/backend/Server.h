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
	explicit Server(const mINI::INIStructure &myINI);
	static void UpdateStatusesTask();
	static void fUpdateTaskStatusTimer(int timeInterval);
	void Initiliaze();
	void RunSERVER();
	void SendMSG(const std::string &MESSAGE, int SocketNum);
};

