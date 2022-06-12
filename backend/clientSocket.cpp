#include "clientSocket.h"
#include <iostream>

clientSocket::clientSocket() 
{
}

clientSocket::~clientSocket() {}

fd_set* clientSocket::GetFD_SET()
{
	return &readfds;
}

SOCKET clientSocket::GetClientArrayById(int i) 
{
	return client_socketArray[i];
}

bool clientSocket::InitClientSocket() 
{
	// add child sockets to fdset
	for (int i = 0; i < 10; i++) {
		SOCKET s = client_socketArray[i];
		if (s > 0) {
			FD_SET(s, &readfds);
		}
	}
	return true;
}

bool clientSocket::AddNewClientToArray(SOCKET &new_socket)
{
	for (int i = 0; i < 10; i++) {
		if (client_socketArray[i] == 0) {
			client_socketArray[i] = new_socket;
			printf("Adding to list of sockets at index %d\n", i);
			break;
		}
	}
	return true;
}