#pragma once
#include <WS2tcpip.h>
#include "Logger.h"

class serverSocket
{
	SOCKET server_socket;
public: 
	serverSocket();
	~serverSocket();
	bool InitializeSocket();
	bool CloseServerSocket();
	bool BindSocket(unsigned short uhSinPort);
	bool Listen(int MAX_CLIENTS);
	bool Accept(SOCKET& new_socket, sockaddr_in &address, int addrlen);

	SOCKET GetServerSocket();
};

