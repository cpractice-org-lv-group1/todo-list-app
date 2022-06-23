#include "Server.h"
#include "Users.h"
#include "Tasks.h"
#include "CRUD.h"
#include <algorithm>
#include "nlohmann/json.hpp"

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

	/*int userId = CRUD::Get<Users>("somethinf").GetCurrentUser().userID;
	cout << userId;*/

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
			SOCKET tempSocket = client_socket.GetClientArrayById(i);
			// if client presend in read sockets
			if (FD_ISSET(tempSocket, client_socket.GetFD_SET()))
			{
				//Check if it was for closing , and also read the 
				//incoming message
				int client_message_length;
				char client_message[DEFAULT_BUFLEN];
				ZeroMemory(client_message, DEFAULT_BUFLEN);
				getpeername(tempSocket, (sockaddr*)&address, (int*)&addrlen);

				client_message_length = recv(tempSocket, client_message, DEFAULT_BUFLEN, 0);
				client_message[client_message_length] = '\0';

				if (client_message_length != 0) {
					string s_client_message(client_message);
					s_client_message.erase(std::remove(s_client_message.begin(), s_client_message.end(), '['), s_client_message.end());
					s_client_message.erase(std::remove(s_client_message.begin(), s_client_message.end(), ']'), s_client_message.end());
					cout << s_client_message << endl << endl;

					nlohmann::json myJSON = nlohmann::json::parse(s_client_message);
					auto jsonIterator = myJSON.find("Operation");

					//LoginGetTasks
					if (jsonIterator.value() == "Login")
					{
						Users user;
						auto tempIt = myJSON.find("Email");
						user = CRUD::Get<Users>(tempIt.value().get<string>());
						int userId = user.GetCurrentUser().userID;
						string userPass((const char*)user.GetCurrentUser().userPassword);
						userPass[userPass.length()] = '\0';

						nlohmann::json result;

						if (userId == 0)
						{
							result["Operation"] = "Login";
							result["Result"] = "Erorr Email";
							result["userID"] = 0;
							SendMSG(result.dump(), i);
						}
						else if (myJSON["Password"].get<string>() != userPass) 
						{
							result["Operation"] = "Login";
							result["Result"] = "Erorr Password";
							result["userID"] = 0;
							SendMSG(result.dump(), i);
						}
						else
						{
							result["Operation"] = "Login";
							result["Result"] = "Success Login";
							result["userID"] = userId;
							SendMSG(result.dump(), i);
						}
					}
					else if (jsonIterator.value() == "GetTasks")
					{
						auto tempIt = myJSON.find("Id");

						int Id = tempIt.value().get<int>();
						auto data = CRUD::Get<Tasks>(Id).GetData();
						if (data.empty())
						{
							SendMSG("Error", i);
						}
						else 
						{
							string result = "[";
							for (int i = 0; i < data.size(); ++i) 
							{
								result += data[i].JSON().dump();
								if (i != data.size() - 1)
								{
									result += ",";
								}
							}
							result += "]";
							SendMSG(result, i);
						}
					}
					else if (jsonIterator.value() == "SignUp")
					{
						nlohmann::json result;
						result["Operation"] = "SignUp";
						bool bSignUpSucces = CRUD::Put<Users>(myJSON);
						if(bSignUpSucces == true)
						{
							result["Result"] = "Success SignUp";
						}
						else 
						{
							result["Result"] = "Erorr SignUp";
						}
						SendMSG(result.dump(), i);
					}
					else if (jsonIterator.value() == "GetUserData")
					{
						auto data = CRUD::Get<Users>(myJSON["user_Id"].get<int>()).GetCurrentData();
						SendMSG(data.JSON(), i);
					}
					else if (jsonIterator.value() == "GetUserFriends")
					{
						
					}
					else 
					{
						cout << "unknown command";
					}
				}
				else {
					printf("Client has been disconected ip is: %s, port: %d\n",inet_ntop(AF_INET, &address.sin_addr, client_message, 512), ntohs(address.sin_port));
					client_socket.clearSocker(i);
				}
			}
		}
	}
}

void Server::SendMSG(std::string MESSAGE, int SocketNum)
{
	send(client_socket.GetClientArrayById(SocketNum), MESSAGE.c_str(), MESSAGE.length(), 0);
}