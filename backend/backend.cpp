#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#define TRUE   1 
#define FALSE  0 
#include "Users.h"
#include "TaskStatuses.h"
#include "Tasks.h"
#include "TaskCategories.h"
#include "FriendStatuses.h"
#include "Friendships.h"
#include "config.h"
#include "CRUD.h"



#define FIELD_LEN 50

using namespace std;

wchar_t* GetWCharFromString(string inString) 
{
    std::wstring wsinString(inString.begin(), inString.end());
    unsigned int maxlength = inString.length() + 1;
    int len = wcsnlen_s(wsinString.c_str(), maxlength);
    wchar_t* outString = new wchar_t[len + 1];

    wcscpy_s(outString, len + 1, wsinString.c_str());

    return outString;
}

void completedConnections() 
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

    cout << "\nPress any key to exit...";
    getchar();
}




int main() 
{
   // //initializations
   // sqlConnHandle = NULL;
   // sqlStmtHandle = NULL;


   // //allocations
   // if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
   //     completedConnections();

   // if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
   //     completedConnections();

   // if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
   //     completedConnections();

   // //output
   // cout << "Attempting connection to SQL Server...";
   // cout << "\n";

   // switch (SQLDriverConnect(sqlConnHandle,
   //     NULL,
   //     (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=mnkserver.database.windows.net, 1433;DATABASE=TodolistDB;UID=sanyok;PWD=!Politech;",
   //     SQL_NTS,
   //     retconstring,
   //     1024,
   //     NULL,
   //     SQL_DRIVER_NOPROMPT)) {

   // case SQL_SUCCESS:
   //     cout << "Successfully connected to SQL Server";
   //     cout << "\n";
   //     break;

   // case SQL_SUCCESS_WITH_INFO:
   //     cout << "Successfully connected to SQL Server";
   //     cout << "\n";
   //     break;

   // case SQL_INVALID_HANDLE:
   //     cout << "Could not connect to SQL Server";
   //     cout << "\n";
   //     completedConnections();

   // case SQL_ERROR:
   //     cout << "Could not connect to SQL Server";
   //     cout << "\n";
   //     completedConnections();

   // default:
   //     break;
   // }

   // //if there is a problem connecting then exit application
   // if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
   //     completedConnections();

   // //output
   // cout << "\n";
   // cout << "Executing query...";
   // cout << "\n";


   // //USERS
   // auto result = CRUD::Get<Users>().GetData();

   //for_each(result.begin(), result.end(), [](auto x) {
   //    x.Print();
   //    });
   //cout << "\n";

   // //TASKS
   //auto result2 = CRUD::Get<Tasks>().GetData();
   // for_each(result2.begin(), result2.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //TASK Statuses
   // auto result3 = CRUD::Get<TaskStatuses>().GetData();
   // for_each(result3.begin(), result3.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //Friendships
   // auto result4 = CRUD::Get<Friendships>().GetData();
   // for_each(result4.begin(), result4.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //Friendship statuses
   // auto result5 = CRUD::Get<FriendStatuses>().GetData();
   // for_each(result5.begin(), result5.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";

   // //TASKS Categories
   // auto result6 = CRUD::Get<TaskCategories>().GetData();
   // for_each(result6.begin(), result6.end(), [](auto x) {
   //     x.Print();
   //     });
   // cout << "\n";


    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOK = WSAStartup(ver, &wsData);

    if (wsOK != 0) {
        cerr << "Can't init winsock";
        return 0;
    }

    int opt = TRUE;
    int master_socket;
    int  addrlen, new_socket, client_socket[30],
    max_clients = 30, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025];  //data buffer of 1K 

    //set of socket descriptors 
    fd_set readfds;

    //a message 
   const char* message = "ECHO";

    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket 
    if ((master_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt,
        sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    const int PORT = 8888;
    //type of socket created 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection 
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE)
    {
        //clear the socket set 
        FD_ZERO(&readfds);

        //add master socket to set 
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set 
        for (i = 0; i < max_clients; i++)
        {
            //socket descriptor 
            sd = client_socket[i];

            //if valid socket descriptor then add to read list 
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function 
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntop(AF_INET, &address.sin_addr.s_addr, buffer, sizeof(buffer)) , ntohs,(address.sin_port));

            //send new connection greeting message 
            if (send(new_socket, message, strlen(message), 0) != strlen(message))
            {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty 
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = recv(sd, buffer, 1024,0)) == 0)
                {
                    //Somebody disconnected , get his details and print 
                    getpeername(sd, (struct sockaddr*)&address, \
                        (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n",
                        inet_ntop(AF_INET, &address.sin_addr.s_addr,buffer,sizeof(buffer)), ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse 
                    closesocket(sd);
                    client_socket[i] = 0;
                }

                //Echo back the message that came in 
                else
                {
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }
    return 0;

}





//void Put()
//{
//    string put = "INSERT INTO Users VALUES('";
//    put += "Name";
//    put += "', 'Surname', '2002 - 01 - 01', 'testmail@gmail.com', 'testpass', 2, 'Novice');";
//
//    wstring wput = GetWCharFromString(put);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wput.c_str(), SQL_NTS);
//}
//
//void Delete(int id)
//{
//    string sqldelete = "Delete from Users where user_Id = ";
//    sqldelete += to_string(id);
//
//    wstring wsqldelete = GetWCharFromString(sqldelete);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wsqldelete.c_str(), SQL_NTS);
//}
//
//void Update(string name, int id)
//{
//    string update = "update Users set user_Name = '";
//    update += name;
//    update += "' where user_id = ";
//    update += to_string(id);
//
//    wstring wupdate = GetWCharFromString(update);
//
//    SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wupdate.c_str(), SQL_NTS);
//}