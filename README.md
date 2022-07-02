# todo-list-app

## ***Technical documentation***

### **Database**:

<img src="https://user-images.githubusercontent.com/84669679/176892811-b1c2b85f-52aa-486e-89b5-6f3c287ce4d1.png"  width="100" height="100"><img src="https://user-images.githubusercontent.com/84669679/176893977-d2f200da-5edf-4f5c-ad71-4e7c060caeb4.png"  width="100" height="100">

Database is hosted on Azure, but all data changes and creation of tables were made using Microsoft SQL Server Management Studio because it is much more user-friendly. Database itself has authorization, using username and password.

### **Backend**:

<img src="https://user-images.githubusercontent.com/84669679/176895378-24630d7a-3a41-46d6-806e-0d2a91ea4291.png"  width="80" height="80">    <img src="https://user-images.githubusercontent.com/84669679/176895916-e432af45-9895-4e4d-99b7-a39316a3218a.png"  width="200" height="100">

Backend is hosted on Azure virtual machine, working 24\7 and can work with up to 10 clients at the same time. All code is C++, to connect we use sockets `WinSock32.h`, and the format of data is JSON. 

To work with it properly, we use `nlohmann` library, which provides easy-to-use functions for JSON format. To work with .ini file, in which you can change port, interval of refreshing data, maximum number if clients and connection string to SQL Server DB, we use `mINI` library. Server also displays the new connections and errors in command prompt, but for detailed information with timestamps about work of server you can also check `server.log` file.

### **Frontend**:

<img src="https://user-images.githubusercontent.com/84669679/176893451-74b61181-7d6d-42b6-a2b8-479ae0066f4f.png"  width="100" height="100">

Frontend client was made in `QT` using `qmake`. It connects to server using sockets from `<QTcpSocket>` library. All code is written on C++. All data requests and reactions to data received from server are connected by signals with proper slots, as well as signals to go from one window to another. To work with `.ini` file we use `<QSettings>` library. To serialize user data and to log the work of programm we use `.txt` files. To display images we use resource group, which contains all needed files.

To help testing all parts of this software, you can use `testing_data.txt` file from this repository, where you can find login details for database and user with most tasks, friends, categories etc.

***

## ***User documentation***
- **How to download this app?**

    [Click to the reference](https://github.com/sbanashchuk-eleks/todo-list-app/releases/download/v1.0.0/frontend.exe.rar) and the download of the program archive will start automatically. If downloading did not start, you can try download archive yourself. Just [click there](https://github.com/sbanashchuk-eleks/todo-list-app/releases/tag/v1.0.0) and then click to archive `frontend.exe` and downloading will start automatically.
- **How to install?**

    Open the archive and unpack to the desired folder.
- **How to start using?**

    Click on `.exe` file, which finds in the unpacked folder, and app will be started. You could see a **LogIn** page. If you have't an account in our system, we recommended create a new account. Click to **SignUp** button:
    
    ![image](https://user-images.githubusercontent.com/84669679/176905472-7b5f7c3f-748b-4230-b6de-0923c3f3b2fa.png)
    
    and you will be redirected to the registration page, where you enter all the necessary data and finally click the button **SignUp**. Returning to the main page, enter the password from the newly created account in the **Password** field. The **Email** field will be filled in automatically, according to the e-mail you specified during registration.
- **What can you do in this app?**

    This application was created so that no person forgets what he plans to do in the near future. Main page has a 3 tasks list columns:

    ![image](https://user-images.githubusercontent.com/84669679/176908808-7db41acf-7374-4989-8a3a-bde8b1e1e3fa.png)

1. In **TODO** column placing a tasks whose execution time has not yet arrived. The circle shows how much time is left until the start of the task.
2. In **IN PROGRESS** column placing a tasks whose execution time has arrived. Tasks marked in red mean that the task completion time has expired.
3. In **DONE** column placing a tasks are marked as completed.

For the add new task, you must click on <img src="https://user-images.githubusercontent.com/84669679/176911049-bd6879f9-b5c6-40af-9991-71d28004ce42.png"  width="80" height="40"> button and a window will open in which you can enter data about a new task.

If click <img src="https://user-images.githubusercontent.com/84669679/176911955-463b4e1c-764f-4361-9d06-5182e1275a11.png" width="80" height="40"> button, will be opened window in wich you can add new, edit, delete custom category.

> You can only do this with custom categories!

You can make a selection of tasks. Just select the category you want to sample and click **Set as current**. You can also make a selection of tasks by time. Write a number in field:

<img src="https://user-images.githubusercontent.com/84669679/176914293-f8b973b2-e097-4992-828b-a67db9d6e609.png" width="140" height="40">

and then click **OK**. Tasks whose start times fall within the specified time are displayed.

On the left side there is information about the user, his friends and a number of additional actions.

![image](https://user-images.githubusercontent.com/84669679/176924564-14aa8d2f-005b-4dc4-81f1-56c76220bab1.png)

1. Exit to start page.
2. History of tasks. There are tasks whose was deleted, done and fastest completed:

<img src="https://user-images.githubusercontent.com/84669679/176925342-e1e97d24-2528-49f4-a28e-0d4b17576af1.png" width="600" height="350">

Search depth is also present here. Just write a number in the field and click **Ok**.
> To go back, just press the button in the same place **Back**

3. Friend requests - shows all friend requests. There you can accept or reject request.
> To go back, just press the button in the same place **Friends**

4. Add friend - after clicking, a dialog box appears, through which you can send a request to a friend, knowing his email.

![image](https://user-images.githubusercontent.com/84669679/176928923-499c24fe-7b43-4c39-82cb-76fc0b479f98.png)

***
