#include "serverSocket.h"
#include <string>
#include <iostream>

serverSocket::serverSocket()
{
	server_socket = INVALID_SOCKET;
}

serverSocket::~serverSocket() 
{
}

bool serverSocket::InitializeSocket()
{
	if ((this->server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
	{
		Logger("{serverSocket.cpp//serverSocket::InitializeSocket} Could not create socket: %d" + WSAGetLastError());	
		return false;
	}

	return true;
}

bool serverSocket::CloseServerSocket() 
{
	bool bRes = false;
	do
	{
		if (server_socket == INVALID_SOCKET)
		{
			break;
		}
		else
		{
			closesocket(server_socket);
			server_socket = INVALID_SOCKET;
		}
		bRes = true;
	} while (false);

	return bRes;
}

bool serverSocket::BindSocket(unsigned short uhSinPort)
{
	// prepare the sockaddr_in structure
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);;
	server.sin_port = htons(uhSinPort);

	// bind socket
	if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) 
	{
		Logger("{serverSocket.cpp//serverSocket::BindSocket} Bind failed with error code: " + WSAGetLastError());
		CloseServerSocket();
		return false;
	}
	return true;
}

bool serverSocket::Listen(int MAX_CLIENTS)
{
	int iListenResult = listen(server_socket, MAX_CLIENTS);;
	return iListenResult != SOCKET_ERROR;
}

bool serverSocket::Accept(SOCKET &new_socket, sockaddr_in &address, int addrlen)
{
	if ((new_socket = accept(server_socket, (sockaddr*)&address, &addrlen)) < 0) {  //=============*ACCEPT*======================
		perror("Accept function error");
		Logger("{serverSocket.cpp//serverSocket::Accept} Accept function error");
		return false;
	}
	return true;
}

SOCKET serverSocket::GetServerSocket() 
{
	return server_socket;
}

