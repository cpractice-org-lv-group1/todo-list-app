#include "Server.h"
#include "Users.h"
#include "Tasks.h"
#include "TaskCategories.h"
#include "Friendships.h"
#include "CRUD.h"
#include <algorithm>
#include "nlohmann/json.hpp"
#include <time.h>
#include <thread>

#define DEFAULT_BUFLEN 4096

Server::Server(const mINI::INIStructure& myINI) : iniCFG(myINI) {};

void Server::UpdateStatusesTask()
{
	auto aTasks = CRUD::Get<Tasks>().GetAllNotStartedTasks();

	for(int i = 0; i < aTasks.size(); ++i)
	{
		std::string taskTime((const char*)aTasks[i].task_Start_Time);
		if (taskTime <= getCurrentTime()) 
		{
			std::string put = "UPDATE Tasks SET ";
			put += "task_Status = 2\
                    where task_Id = " + std::to_string(aTasks[i].task_Id) + ";";
			std::wstring wput = GetWCharFromString(put);
			SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);
		}
	}
}

void Server::fUpdateTaskStatusTimer(int timeInterval)
{
    time_t start;
	start = time(0);
	int interval = timeInterval;

	while (true) 
	{
		if (time(0) - start == interval) 
		{
			UpdateStatusesTask();
			start = start + interval;
		}
	}
}

void Server::Initiliaze()
{
	server_socket.InitializeSocket();

	server_socket.BindSocket(stoi(iniCFG["Options"]["PORT"]));

	server_socket.Listen(stoi(iniCFG["Options"]["MAX_CLIENTS"]));
}

void Server::RunSERVER() 
{
	//initializations
    sqlConnHandle = nullptr;
    sqlStmtHandle = nullptr;

    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        completedConnections();

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        completedConnections();

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        completedConnections();

	std::cout << "Attempting connection to SQL Server...";
	std::cout << "\n";
	Logger("Attempting connection to SQL Server...");

    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        (SQLWCHAR*)GetWCharFromString(iniCFG["Options"]["DBConnectString"]),
        SQL_NTS,
        retconstring,
        1024,
        nullptr,
        SQL_DRIVER_NOPROMPT)) {

    case SQL_SUCCESS || SQL_SUCCESS_WITH_INFO :
		std::cout << "Successfully connected to SQL Server";
		std::cout << "\n";
		Logger("Successfully connected to SQL Server");
        break;

    case SQL_INVALID_HANDLE:
		std::cout << "Could not connect to SQL Server";
		std::cout << "\n";
		Logger("Could not connect to SQL Server");
        completedConnections();

    case SQL_ERROR:
		std::cout << "Could not connect to SQL Server";
		std::cout << "\n";
		Logger("Could not connect to SQL Server");
        completedConnections();

    default:
        break;
    }

    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        completedConnections();

	Initiliaze();

	//--------------------UPDATE STATUS TASK THREAD-----------------------------------------------
	std::thread thUpdateStatusTask(fUpdateTaskStatusTimer, stoi(iniCFG["Options"]["SECONDS_OF_UPDATING_TASKSTATUS"]));
	thUpdateStatusTask.detach();
	//--------------------------------------------------------------------------------------------

	while (true) {
		// clear the socket fdset
		FD_ZERO(client_socket.GetFD_SET());

		// add master socket to fdset
		FD_SET(server_socket.GetServerSocket(), client_socket.GetFD_SET());
		
		client_socket.InitClientSocket();

		// wait for an activity on any of the sockets, timeout is NULL, so wait indefinitely
		if (select(0, client_socket.GetFD_SET(), nullptr, nullptr, nullptr) == SOCKET_ERROR) 
		{
			Logger("Select function call failed with error code :" + WSAGetLastError());
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
				Logger("Exiting from server: ACCEPT error");
				std::cout << "Exit";
				return;
			};
			char buf[512];
			printf("New connection, socket fd is %I64u, ip is: %s, port: %d\n", new_socket, inet_ntop(AF_INET, &address.sin_addr,buf,512), ntohs(address.sin_port));
			
			std::string str(inet_ntop(AF_INET, &address.sin_addr, buf, 512));
			std::string outputLog = "New connection, socket fd is " + new_socket;
			outputLog += "IP is: " + str + " PORT: " + std::to_string(ntohs(address.sin_port));
			Logger(outputLog);

			client_socket.AddNewClientToArray(new_socket);
		}
		

		// if some of client sockets sends something
		for (int i = 0; i < stoi(iniCFG["Options"]["MAX_CLIENTS"]); i++)
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
					std::string s_client_message(client_message);
					s_client_message.erase(std::remove(s_client_message.begin(), s_client_message.end(), '['), s_client_message.end());
					s_client_message.erase(std::remove(s_client_message.begin(), s_client_message.end(), ']'), s_client_message.end());

					nlohmann::json myJSON = nlohmann::json::parse(s_client_message);
					auto jsonIterator = myJSON.find("Operation");

					
					if (jsonIterator.value() == "Login")  //LOGIN
					{
						Users user;
						auto tempIt = myJSON.find("Email");
						user = CRUD::Get<Users>(tempIt.value().get<std::string>());
						int userId = user.GetCurrentUser().userID;
						std::string userPass((const char*)user.GetCurrentUser().userPassword);
						userPass[userPass.length()] = '\0';

						Logger("Login User Mail" + tempIt.value().get<std::string>());

						nlohmann::json result;

						if (userId == 0) //UNKNOWN USER
						{
							result["Operation"] = "Login";
							result["Result"] = "Erorr Email";
							result["userID"] = 0;
							SendMSG(result.dump(), i);
							Logger("User Email Error");
						}
						else if (myJSON["Password"].get<std::string>() != userPass) //UNCORRECT USER password
						{
							result["Operation"] = "Login";
							result["Result"] = "Erorr Password";
							result["userID"] = 0;
							SendMSG(result.dump(), i);
							Logger("User Password Error");
						}
						else                                //SUCCES login
						{
							result["Operation"] = "Login";
							result["Result"] = "Success Login";
							result["userID"] = userId;
							SendMSG(result.dump(), i);
							Logger("User LOGIN SUCCESFULL");
						}
					}
					else if (jsonIterator.value() == "GetTasks") //GET TASKS
					{
						auto tempIt = myJSON.find("Id");
						Logger(" Get Tasks for userId = " + std::to_string(tempIt.value().get<int>()));

						int Id = tempIt.value().get<int>();
						auto data = CRUD::Get<Tasks>(Id).GetData();
						if (data.empty())
						{
							SendMSG("[{\"IsEmpty\":1,\"task_Id\": 1}]", i);
							Logger("There is no tasks for this user");
						}
						else 
						{
							std::string result = "[";
							for (int i = 0; i < data.size(); ++i) 
							{
								result += data[i].JSON().dump();
								if (i != data.size() - 1)
								{
									result += ",";
								}
							}
							result += "]";
							std::cout << result + "\n";
							SendMSG(result, i);
						}
					}
					else if (jsonIterator.value() == "SignUp") //NEW USER
					{
						nlohmann::json result;
						result["Operation"] = "SignUp";
						bool bSignUpSucces = CRUD::Post<Users>(myJSON);
						Logger("SignUp new User function");

						if(bSignUpSucces == true)
						{
							result["Result"] = "Success SignUp";
						}
						else 
						{
							result["Result"] = "Erorr SignUp";
							Logger("Erorr SignUp");
						}
						SendMSG(result.dump(), i);
					}
					else if (jsonIterator.value() == "GetUserData")
					{
						auto data = CRUD::Get<Users>(myJSON["Id"].get<int>()).GetCurrentData();
						Logger("Getting UserData");
						nlohmann::json tempJson = nlohmann::json::parse(data.JSON());
						tempJson["Operation"] = "GetUserData";
						SendMSG(tempJson.dump(), i);
					}
					else if (jsonIterator.value() == "GetUserFriends") // GET FRIENDS
					{
						auto data = CRUD::Get<Friendships>(myJSON["Id"].get<int>()).GetAllFriends();
						Logger(" Getting friends for userId = " + std::to_string(myJSON["Id"].get<int>()));

						if (data.empty())
						{
							SendMSG("[{\"IsEmpty\":1,\"user_Id\": 1}]", i);
							Logger("There are no friends for this user");
						}
						else 
						{
							std::string result = "[";
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
					else if (jsonIterator.value() == "GetCategories") //GET CATEGORIES
					{
						auto data = CRUD::Get<TaskCategories>(myJSON["Id"].get<int>()).GetData();
						Logger(" Getting Categories for userId = " + std::to_string(myJSON["Id"].get<int>()));

						std::string result = "[";
						for (int i = 0; i < data.size(); ++i)
						{
							result += data[i].JSON();
							if (i != data.size() - 1)
							{
								result += ",";
							}
						}
						result += "]";
						SendMSG(result, i);
					}
					else if (jsonIterator.value() == "PostTask") //NEW TASK
					{
						auto result = CRUD::Post<Tasks>(myJSON);
						
						if (result == true)
						{
							SendMSG("{ \"Operation\":\"PostTaskResult\", \"Result\" : \"Success\" }", i);
							Logger("New Task added");
						}
						else
						{
							SendMSG("{ \"Operation\":\"PostTaskResult\", \"Result\" : \"Error\" }", i);
							Logger("New Task failed add");
						}
					}
					else if (jsonIterator.value() == "PostCategory") //NEW CATEGORY
					{
						auto result = CRUD::Post<TaskCategories>(myJSON);
						
						if (result == true)
						{
							SendMSG("{ \"Operation\":\"PostCategoryResult\", \"Result\" : \"Success\" }", i);
							Logger("New Category added");
						}
						else
						{
							SendMSG("{ \"Operation\":\"PostCategoryResult\", \"Result\" : \"Error\" }", i);
							Logger("New Category failed add");
						}
					}
					else if (jsonIterator.value() == "PutTask") //EDIT TASK
					{
						auto result = CRUD::Put<Tasks>(myJSON);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"PutTaskResult\", \"Result\" : \"Success\" }", i);
							Logger("Edited Task success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"PutTaskResult\", \"Result\" : \"Error\" }", i);
							Logger("Edited Task failed");
						}
					}
					else if (jsonIterator.value() == "PutCategory") //EDIT CATEGORY
					{
					auto result = CRUD::Put<TaskCategories>(myJSON);

					if (result == true)
					{
						SendMSG("{ \"Operation\":\"PutCategoryResult\", \"Result\" : \"Success\" }", i);
						Logger("Edited Category success");
					}
					else
					{
						SendMSG("{ \"Operation\":\"PutCategoryResult\", \"Result\" : \"Error\" }", i);
						Logger("Edited Category failed");
					}
					}
					else if (jsonIterator.value() == "DeleteTask") //DELETE TASK
					{
						int id = myJSON["task_Id"].get<int>();
						auto result = CRUD::Delete<Tasks>(id);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"DeleteTaskResult\", \"Result\" : \"Success\" }", i);
							Logger("DELETE Task success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"DeleteTaskResult\", \"Result\" : \"Error\" }", i);
							Logger("DELETE Task failed");
						}
					}
					else if (jsonIterator.value() == "DeleteCategory") //DELETE CATEGORY
					{
						int id = myJSON["taskCategories_Id"].get<int>();
						auto result = CRUD::Delete<TaskCategories>(id);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"DeleteCategoryResult\", \"Result\" : \"Success\" }", i);
							Logger("DELETE Category success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"DeleteCategoryResult\", \"Result\" : \"Error\" }", i);
							Logger("DELETE Category failed");
						}
					}
					else if (jsonIterator.value() == "DeleteFriend") //DELETE FRIENDSHIP
					{
						int id = myJSON["friendship_Id"].get<int>();
						auto result = CRUD::Delete<Friendships>(id);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"DeleteFriendResult\", \"Result\" : \"Success\" }", i);
							Logger("DELETE Friendships success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"DeleteFriendResult\", \"Result\" : \"Error\" }", i);
							Logger("DELETE Friendships failed");
						}
					}
					else if (jsonIterator.value() == "PostCategory") //POST CATEGORY
					{
						auto result = CRUD::Post<TaskCategories>(myJSON);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"PostCategoryResult\", \"Result\" : \"Success\" }", i);
							Logger("New Category success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"PostCategoryResult\", \"Result\" : \"Error\" }", i);
							Logger("New Category failed");
						}
					}
					else if (jsonIterator.value() == "AddFriend") //POST FRIENDSHIP
					{
						auto result = CRUD::Post<Friendships>(myJSON);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"AddFriendResult\", \"Result\" : \"Success\" }", i);
							Logger("Add Friendships success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"AddFriendResult\", \"Result\" : \"Error\" }", i);
							Logger("Add Friendships failed");
						}
					}
					else if (jsonIterator.value() == "FriendRequestAnswer") //ACCEPT FRIENDSHIP
					{
						auto result = CRUD::Put<Friendships>(myJSON);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"FriendRequestAnswerResult\", \"Result\" : \"Success\" }", i);
							Logger("FriendRequestAnswer success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"FriendRequestAnswerResult\", \"Result\" : \"Error\" }", i);
							Logger("FriendRequestAnswer failed");
						}
					}
					else if (jsonIterator.value() == "CompleteTask") //COMPLETE TASK
					{
						auto result = CRUD::Put<Users>(myJSON);

						if (result == true)
						{
							SendMSG("{ \"Operation\":\"CompleteTaskResult\", \"Result\" : \"Success\" }", i);
							Logger("CompleteTask success");
						}
						else
						{
							SendMSG("{ \"Operation\":\"CompleteTaskResult\", \"Result\" : \"Error\" }", i);
							Logger("CompleteTask failed");
						}
					}
					else 
					{
						std::cout << "Unknown command";
						Logger("Unknown command");
					}
				}
				else 
				{
					printf("Client has been disconected ip is: %s, port: %d\n",inet_ntop(AF_INET, &address.sin_addr, client_message, 512), ntohs(address.sin_port));
					std::string str(inet_ntop(AF_INET, &address.sin_addr, client_message, 512));
					std::string outputLog = "Client has been disconected IP is: " + str + " PORT: " + std::to_string(ntohs(address.sin_port));
					Logger(outputLog);

					client_socket.clearSocker(i);
				}
			}
		}
	}
}

void Server::SendMSG(const std::string &MESSAGE, int SocketNum)
{
	send(client_socket.GetClientArrayById(SocketNum), MESSAGE.c_str(), MESSAGE.length(), 0);
}