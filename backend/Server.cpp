#include "Server.h"
#define DEFAULT_BUFLEN 4096

void Server::Initiliaze() 
{
	server_socket.InitializeSocket();

	server_socket.BindSocket(8888);

	server_socket.Listen(10);
}

void Server::RunSERVER() 
{
	Initiliaze();

	while (true) {
		// clear the socket fdset
		FD_ZERO(client_socket.GetFD_SET());

		// add master socket to fdset
		FD_SET(server_socket.GetServerSocket(), client_socket.GetFD_SET());
		
		client_socket.InitClientSocket();

		// wait for an activity on any of the sockets, timeout is NULL, so wait indefinitely
		if (select(0, client_socket.GetFD_SET(), NULL, NULL, NULL) == SOCKET_ERROR) 
		{
			printf("select function call failed with error code : %d", WSAGetLastError());
			return;
		} 

		// if something happened on the master socket, then its an incoming connection
		SOCKET new_socket;
		sockaddr_in address;
		int addrlen = sizeof(sockaddr_in);

		if (FD_ISSET(server_socket.GetServerSocket(), client_socket.GetFD_SET())) 
		{
			if (!server_socket.Accept(new_socket, address, addrlen)) 
			{
				std::cout << "Exiting from server: ACCEPT error";
				return;
			};
			char buf[4096];
			printf("New connection, socket fd is %d, ip is: %s, port: %d\n", new_socket,inet_ntop(AF_INET, &address.sin_addr,buf,4096), ntohs(address.sin_port));

			client_socket.AddNewClientToArray(new_socket);
		}

		// if some of client sockets sends something
		for (int i = 0; i < 10; i++)
		{
			SOCKET s = client_socket.GetClientArrayById(i);
			// if client presend in read sockets
			if (FD_ISSET(s, client_socket.GetFD_SET()))
			{
				// get details of the client
				getpeername(s, (sockaddr*)&address, (int*)&addrlen);

				// check if it was for closing, and also read the incoming message
				// recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one)

				char client_message[DEFAULT_BUFLEN];

				int client_message_length = recv(s, client_message, DEFAULT_BUFLEN, 0);
				client_message[client_message_length] = '\0';

				for (int i = 0; i < 10; i++) {
					if (client_socket.GetClientArrayById(i) != 0) {
						SendMSG(client_message, i);
					}
				}

			}
		}
	}

}

void Server::SendMSG(std::string MESSAGE, int SocketNum)
{
	send(client_socket.GetClientArrayById(SocketNum), MESSAGE.c_str(), MESSAGE.length(), 0);
}