#include "Server.h"
#include "Users.h"
#include "CRUD.h"
#define DEFAULT_BUFLEN 4096

void Server::Initiliaze() 
{
	server_socket.InitializeSocket();

	server_socket.BindSocket(8888);

	server_socket.Listen(10);
}

bool myCompare(char* first, char* second, int length) 
{
	for (int i = 0; i < length; i++) {
		if (first[i] != second[i]) 
		{
			return false;
		}
	}
	return true;
}


void Server::RunSERVER() 
{
	//initializations
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;

    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        completedConnections();

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        completedConnections();

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        completedConnections();

    //output
    cout << "Attempting connection to SQL Server...";
    cout << "\n";

    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=mnkserver.database.windows.net, 1433;DATABASE=TodolistDB;UID=sanyok;PWD=!Politech;",
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {

    case SQL_SUCCESS || SQL_SUCCESS_WITH_INFO :
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;

    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        completedConnections();

    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        completedConnections();

    default:
        break;
    }

    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        completedConnections();

    //output
    cout << "\n";
    cout << "Executing query...";
    cout << "\n";


    //USERS
    auto users = CRUD::Get<Users>("ivanglina").GetCurrentUser();
	users.Print();
 /*  for_each(users.begin(), users.end(), [](auto x) {
       x.Print();
       });
   cout << "\n";*/

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
			char buf[512];
			printf("New connection, socket fd is %d, ip is: %s, port: %d\n", new_socket,inet_ntop(AF_INET, &address.sin_addr,buf,512), ntohs(address.sin_port));

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

				char client_message[DEFAULT_BUFLEN];

				int client_message_length = recv(s, client_message, DEFAULT_BUFLEN, 0);

				char hello[5] = { 'h','e','l','l', 'o' };

				if (myCompare(client_message, hello, 5)) 
				{
					//SendMSG(users[0].JSON(), i);
				}
			}
		}
	}

}

void Server::SendMSG(std::string MESSAGE, int SocketNum)
{
	send(client_socket.GetClientArrayById(SocketNum), MESSAGE.c_str(), MESSAGE.length(), 0);
}