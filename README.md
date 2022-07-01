# todo-list-app

Technical documentation

Database:
Database is hosted on Azure, but all data changes and creation of tables were made using Microsoft SQL Server Management Studio because it is much more user-friendly. Database itself has authorization, using username and password.

Backend:
Backend is hosted on Azure virtual machine, working 24\7 and can work with up to 10 clients at the same time. All code is C++, to connect we use sockets(WinSock32.h), and the format of data is JSON. To work with it properly, we use "nlohmann" library, which provides easy-to-use functions for JSON format. To work with .ini file, in which you can change port, interval of refreshing data, maximum number if clients and connection string to SQL Server DB, we use "mINI" library. Server also displays the new connections and errors in command prompt, but for detailed information with timestamps about work of server you can also check server.log file.

Frontend:
Frontend client was made in QT using qmake. It connects to server using sockets from <QTcpSocket> library. All code is written on C++. All data requests and reactions to data received from server are connected by signals with proper slots, as well as signals to go from one window to another. To work with .ini file we use <QSettings> library. To serialize user data and to log the work of programm we use .txt files. To display images we use resource group, which contains all needed files.

