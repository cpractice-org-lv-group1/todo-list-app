#ifndef DATAFILLHELPER_H
#define DATAFILLHELPER_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QJsonObject>
#include <vector>
#include <algorithm>
#include <QLabel>
using namespace std;

class DataFillHelper
{
public:
    DataFillHelper();
    static void FillWithTasks(QListWidget* Todo, QListWidget* InProgress, QListWidget* Done, vector<QJsonObject> Tasks, int depth, QString category);
    static void FillWithHistoryTasks(QListWidget* Fastest, QListWidget* Deleted, QListWidget* Done, vector<QJsonObject> Tasks, int depth);
    static void FillUserData(QLabel * Name, QLabel * RankName, QLabel * Points, QLabel * Icon, QJsonObject User);
};

#endif // DATAFILLHELPER_H
