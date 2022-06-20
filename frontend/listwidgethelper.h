#ifndef LISTWIDGETHELPER_H
#define LISTWIDGETHELPER_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QJsonObject>
#include <vector>
using namespace std;

class ListWidgetHelper
{
public:
    ListWidgetHelper();
    static void FillWithTasks(QListWidget* Todo, QListWidget* InProgress, QListWidget* Done, vector<QJsonObject> Tasks);
};

#endif // LISTWIDGETHELPER_H
