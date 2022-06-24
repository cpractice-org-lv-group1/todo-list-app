#pragma once
#include "clientSocket.h"
#include "serverSocket.h"
#include <string>
#include <iostream>

class Server
{
	clientSocket client_socket;
	serverSocket server_socket;
public:
	void Initiliaze();
	void RunSERVER();
	void SendMSG(std::string MESSAGE, int SocketNum);
};

