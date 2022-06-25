#include "datafillhelper.h"

DataFillHelper::DataFillHelper()
{

}

void DataFillHelper::FillWithTasks(QListWidget* Todo, QListWidget* InProgress, QListWidget* Done, vector<QJsonObject> Tasks, int depth, QString category)
{
    //CLEAR FROM PREVIOUS DATA
    Todo->clear();
    InProgress->clear();
    Done->clear();

    //CATEGORY SELECTOR
    vector<QJsonObject> TasksVector;

    if(category == "All Categories") TasksVector = Tasks;
    else
    {
        for(const auto &x : Tasks)
        {
            if(x.value("task_Category").toString() == category)
            {
                TasksVector.emplace_back(x);
            }
        }
    }
    //FIll
    //AMOUNT OF SECONDS RIGHT NOW FROM YEAR 0
    long long currentseconds = 0;
    QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    currentseconds += currenttime.sliced(0, 4).toLongLong() * 31536000;
    currentseconds += currenttime.sliced(5, 2).toLongLong() * 2628288;
    currentseconds += currenttime.sliced(8, 2).toLongLong() * 86400;
    currentseconds += currenttime.sliced(11, 2).toLongLong() * 3600;
    currentseconds += currenttime.sliced(14, 2).toLongLong() * 60;
    currentseconds += currenttime.sliced(17, 2).toLongLong();
    for(const auto &x : TasksVector)
    {
        //SKIP DELETED
        if(x.value("task_Status").toString() == "Deleted") continue;
        QString TaskHeader, TaskBody;
        TaskHeader = x.value("task_Header").toString();
        TaskBody = x.value("task_Body").toString();

        //I HIDE TASK ID IN THIS STRING TO USE IT LATER FOR LOGIC, BUT IT CANNOT BE SEEN BT USER
        QString stringresult = TaskHeader + "\n" + TaskBody + "                          " + QString::number(x.value("task_Id").toDouble());
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(stringresult);

        QString starttime = x.value("task_Start_Time").toString();
        QString endtime = x.value("task_Expected_End_Time").toString();

        //AMOUNT OF SECONDS FOR START TIME FROM YEAR 0
        long long startseconds = 0;
        startseconds += starttime.sliced(0, 4).toLongLong() * 31536000;
        startseconds += starttime.sliced(5, 2).toLongLong() * 2628288;
        startseconds += starttime.sliced(8, 2).toLongLong() * 86400;
        startseconds += starttime.sliced(11, 2).toLongLong() * 3600;
        startseconds += starttime.sliced(14, 2).toLongLong() * 60;
        startseconds += starttime.sliced(17, 2).toLongLong();

        long long endseconds = 0;
        endseconds += endtime.sliced(0, 4).toLongLong() * 31536000;
        endseconds += endtime.sliced(5, 2).toLongLong() * 2628288;
        endseconds += endtime.sliced(8, 2).toLongLong() * 86400;
        endseconds += endtime.sliced(11, 2).toLongLong() * 3600;
        endseconds += endtime.sliced(14, 2).toLongLong()  * 60;
        endseconds += endtime.sliced(17, 2).toLongLong();

        //IF IT IS OUTDATED
        if(currentseconds > startseconds)
        {
            //IF IT IS FINISHED
            if(x.value("task_Real_End_Time").toString() != "None")
            {
                QString end = x.value("task_Real_End_Time").toString();
                long long endsecs = 0;
                endsecs += end.sliced(0, 4).toLongLong() * 31536000;
                endsecs += end.sliced(5, 2).toLongLong() * 2628288;
                endsecs += end.sliced(8, 2).toLongLong() * 86400;
                endsecs += end.sliced(11, 2).toLongLong() * 3600;
                endsecs += end.sliced(14, 2).toLongLong()  * 60;
                endsecs += end.sliced(17, 2).toLongLong();
                if((currentseconds - endsecs) < (depth * 3600))
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/done.png"));
                    Done->addItem(newItem);
                }
            }
            //IF IT IS NOT FINISHED
            else
            {
                //IF IT IS LATE
                if(endseconds < currentseconds)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/late.png"));
                    InProgress->addItem(newItem);
                    newItem->setForeground(QColor("red"));
                }
                //IF IT IS IN PROGRESS
                else
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/progress.png"));
                    InProgress->addItem(newItem);
                }
            }
        }
        //IF IT HAS NOT STARTED YET
        else
        {
            long long difference = startseconds - currentseconds;
            //CASES FOR DIFFERENCE
            if(difference < (depth * 3600))
            {
                if(difference > 31536000)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test1y.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <= 31536000 && difference > 2628288)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test1m.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <= 2628288 && difference > 86400 * 7)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test1w.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <= 86400 * 7 && difference > 86400 * 5)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test5day.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <= 86400 * 5 && difference > 86400 * 3)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test3day.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <= 86400 * 3 && difference > 86400)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test1day.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <= 86400 && difference > 3600 * 9)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test9h.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <=  3600 * 9 && difference > 3600 * 6)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test6h.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <=  3600 * 6 && difference > 3600 * 3)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test3h.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <  3600 * 3 && difference > 3600 * 2)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test2h.png"));
                    Todo->addItem(newItem);
                }
                else if(difference <  3600 * 2)
                {
                    newItem->setIcon(QIcon(":/Img/TimeIcons/test1h.png"));
                    Todo->addItem(newItem);
                }
            }
        }
    }
}

void DataFillHelper::FillWithHistoryTasks(QListWidget* Fastest, QListWidget* Deleted, QListWidget* Done, vector<QJsonObject> Tasks, int depth)
{
    if(depth < 1) return;
    Fastest->clear();
    Deleted->clear();
    Done->clear();

    //FASTEST
    vector<pair<QJsonObject, long>> done;
    for(const auto &x : Tasks)
    {
        if(x.value("task_Status").toString() == "Completed")
        {
            done.emplace_back(make_pair(x, 0));
        }
    }

    int maxdepth = depth;
    if(done.size() > 1)
    {
        for_each(done.begin(), done.end(), [](auto &a)
        {
            QString starttimeA = a.first.value("task_Start_Time").toString();
            QString endtimeA = a.first.value("task_Real_End_Time").toString();
            long long startsecondsA = 0;
            startsecondsA += starttimeA.sliced(0, 4).toLongLong() * 31536000;
            startsecondsA += starttimeA.sliced(5, 2).toLongLong() * 2628288;
            startsecondsA += starttimeA.sliced(8, 2).toLongLong() * 86400;
            startsecondsA += starttimeA.sliced(11, 2).toLongLong() * 3600;
            startsecondsA += starttimeA.sliced(14, 2).toLongLong() * 60;
            startsecondsA += starttimeA.sliced(17, 2).toLongLong();
            long long endsecondsA = 0;
            endsecondsA += endtimeA.sliced(0, 4).toLongLong() * 31536000;
            endsecondsA += endtimeA.sliced(5, 2).toLongLong() * 2628288;
            endsecondsA += endtimeA.sliced(8, 2).toLongLong() * 86400;
            endsecondsA += endtimeA.sliced(11, 2).toLongLong() * 3600;
            endsecondsA += endtimeA.sliced(14, 2).toLongLong()  * 60;
            endsecondsA += endtimeA.sliced(17, 2).toLongLong();

            a.second = endsecondsA - startsecondsA;
        });

        sort(done.begin(), done.end(), [](auto &a, auto &b)
        {
            return a.second < b.second;
        });

        for(const auto &x : done)
        {
            double hours = x.second / 3600.0;
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setIcon(QIcon(":/Img/TimeIcons/done.png"));
            QString stringresult = "(" + QString::number(hours) + " h)" + x.first.value("task_Header").toString() + "\n" + x.first.value("task_Body").toString() + "                          " + QString::number(x.first.value("task_Id").toDouble());
            newItem->setText(stringresult);
            Fastest->addItem(newItem);
            maxdepth--;
            if(!maxdepth) break;
        }
    }

    //DELETED
    maxdepth = depth;
    for(const auto &x : Tasks)
    {
        if(x.value("task_Status").toString() == "Deleted")
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setIcon(QIcon(":/Img/TimeIcons/deleted.png"));
            QString stringresult = x.value("task_Header").toString() + "\n" + x.value("task_Body").toString() + "                          " + QString::number(x.value("task_Id").toDouble());
            newItem->setText(stringresult);
            Deleted->addItem(newItem);
            maxdepth--;
            if(!maxdepth) break;
        }
    }
    //DONE
    maxdepth = depth;
    for(const auto &x : Tasks)
    {
        if(x.value("task_Status").toString() == "Completed")
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setIcon(QIcon(":/Img/TimeIcons/done.png"));
            QString stringresult = x.value("task_Header").toString() + "\n" + x.value("task_Body").toString() + "                          " + QString::number(x.value("task_Id").toDouble());
            newItem->setText(stringresult);
            Done->addItem(newItem);
            maxdepth--;
            if(!maxdepth) break;
        }
    }
}

void DataFillHelper::FillUserData(QLabel * Name, QLabel * RankName, QLabel * Points, QLabel * Icon, QJsonObject User)
{
    QString rankName = User.value("userRank").toString();
    Name->setText(User.value("userNameArr").toString() + " " + User.value("userSurnameArr").toString());
    RankName->setText("Rank: " + rankName);
    Points->setText("Points: " + QString::number(User.value("userPoints").toDouble()));
    if(rankName == "Novice")
    {
        QPixmap pix(":/Img/Ranks/silver.png");
        Icon->setPixmap(pix);
        return;
    }
    else if(rankName == "Gold")
    {
        QPixmap pix(":/Img/Ranks/gold.png");
        Icon->setPixmap(pix);
        return;
    }
    else if(rankName == "Platinum")
    {
        QPixmap pix(":/Img/Ranks/platinum.png");
        Icon->setPixmap(pix);
        return;
    }
    else if(rankName == "Diamomd")
    {
        QPixmap pix(":/Img/Ranks/diamond.png");
        Icon->setPixmap(pix);
        return;
    }
    else
    {
        QPixmap pix(":/Img/Ranks/immortal.png");
        Icon->setPixmap(pix);
        return;
    }
}


//FULL FRIENDLIST
void DataFillHelper::FillFriends(QListWidget* List, vector<QJsonObject> Friends)
{
    List->clear();

    for(const auto &x : Friends)
    {
        if(x.value("friend_status_Name").toString() == "added")
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(x.value("user_Name").toString() + " " + x.value("user_Surname").toString());
            if(x.value("user_Rank").toString() == "Novice")
            {
                newItem->setIcon(QIcon(":/Img/Ranks/silver.png"));
                List->addItem(newItem);
            }
            else if(x.value("user_Rank").toString() == "Gold")
            {
                newItem->setIcon(QIcon(":/Img/Ranks/gold.png"));
                List->addItem(newItem);
            }
            else if(x.value("user_Rank").toString() == "Platinum")
            {
                newItem->setIcon(QIcon(":/Img/Ranks/platinum.png"));
                List->addItem(newItem);
            }
            else if(x.value("user_Rank").toString() == "Diamomd")
            {
                newItem->setIcon(QIcon(":/Img/Ranks/diamond.png"));
                List->addItem(newItem);
            }
            else
            {
                newItem->setIcon(QIcon(":/Img/Ranks/immortal.png"));
                List->addItem(newItem);
            }
        }
    }
}






