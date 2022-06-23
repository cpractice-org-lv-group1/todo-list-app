#ifndef DATAFILLHELPER_H
#define DATAFILLHELPER_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QJsonObject>
#include <vector>
#include <algorithm>
using namespace std;

class DataFillHelper
{
public:
    DataFillHelper();
    static void FillWithTasks(QListWidget* Todo, QListWidget* InProgress, QListWidget* Done, vector<QJsonObject> Tasks);
    static void FillWithHistoryTasks(QListWidget* Fastest, QListWidget* Deleted, QListWidget* Done, vector<QJsonObject> Tasks, int depth);
};

#endif // DATAFILLHELPER_H
