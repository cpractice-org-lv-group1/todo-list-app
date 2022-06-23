#include "datafillhelper.h"

DataFillHelper::DataFillHelper()
{

}

//WARNING!! HAVE TO REMAKE AFTER FORIEGN KEYS ARE DONE!!
void DataFillHelper::FillWithTasks(QListWidget* Todo, QListWidget* InProgress, QListWidget* Done, vector<QJsonObject> Tasks)
{
    //CLEAR FROM PREVIOUS DATA
    Todo->clear();
    InProgress->clear();
    Done->clear();
    //FIll

    //AMOUNT OF SECONDS RIGHT NOW FROM YEAR 0
    long long currentseconds = 0;
    QString currenttime = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:ss:mm");//3h 10m
    currentseconds += currenttime.sliced(0, 4).toLongLong() * 31536000;
    currentseconds += currenttime.sliced(5, 2).toLongLong() * 2628288;
    currentseconds += currenttime.sliced(8, 2).toLongLong() * 86400;
    currentseconds += (currenttime.sliced(11, 2).toLongLong() + 3) * 3600;
    currentseconds += (currenttime.sliced(14, 2).toLongLong() + 10) * 60;
    currentseconds += currenttime.sliced(17, 2).toLongLong();
    for(const auto &x : Tasks)
    {
        //SKIP DELETED
        if(x.value("task_Status").toDouble() == 4) continue;
        //MARE SURE THAT TEXT DOES NOT OVERFLOW
        QString TaskHeader, TaskBody;
//        if(x.value("task_Header").toString().length() >= 18)
//        {
//            TaskHeader = x.value("task_Header").toString();
//            int index = TaskHeader.length() - 1;
//            while(1)
//            {
//                if(TaskHeader[index] == ' ' && index < 18) break;
//                index--;
//            }
//            TaskHeader = x.value("task_Header").toString().sliced(0, index) + "...";
//        }
//        else
            TaskHeader = x.value("task_Header").toString();

//        if(x.value("task_Body").toString().length() >= 18)
//        {
//            TaskBody = x.value("task_Body").toString();
//            int index = TaskBody.length() - 1;
//            while(1)
//            {
//                if(TaskBody[index] == ' ' && index < 18) break;
//                index--;
//            }
//            TaskBody = x.value("task_Body").toString().sliced(0, index) + "...";
//        }
//        else
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
                if(((currentseconds - endsecs) / 3600.0) < 3.0)
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

//WARNING!! HAVE TO REMAKE AFTER FORIEGN KEYS ARE DONE!!
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
        if(x.value("task_Status").toDouble() == 3)
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
        if(x.value("task_Status").toDouble() == 4)
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
        if(x.value("task_Status").toDouble() == 3)
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




