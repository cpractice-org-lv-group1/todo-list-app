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

SOCKET clientSocket::GetClientArrayById(int i) const
{
	return client_socketArray[i];
}

void clientSocket::clearSocker(int i)
{
	client_socketArray[i] = 0;
}

bool clientSocket::InitClientSocket() 
{
	// add child sockets to fdset
	for(const auto &x: client_socketArray) {
		SOCKET s = x;
		if (s > 0) {
			FD_SET(s, &readfds);
		}
	}
	return true;
}

bool clientSocket::AddNewClientToArray(SOCKET &new_socket)
{
	int i = 0;
	for (auto &x: client_socketArray) {
		if (x == 0) {
			x = new_socket;
			printf("Adding to list of sockets at index %d\n", i);
			Logger("Adding to list of sockets at index " + std::to_string(i));
			break;
		}
		i++;
	}
	return true;
}