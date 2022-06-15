#pragma once
#include <WS2tcpip.h>

class clientSocket
{
public:
	clientSocket();
	~clientSocket();
	bool InitClientSocket();
	bool AddNewClientToArray(SOCKET &new_socket);

	fd_set* GetFD_SET();
	SOCKET GetClientArrayById(int i);
	void clearSocket(int i);
private:
	fd_set readfds;
	SOCKET client_socketArray[10] = {};
};

