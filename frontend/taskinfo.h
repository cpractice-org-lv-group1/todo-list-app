#ifndef TASKINFO_H
#define TASKINFO_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <vector>
#include "logwriter.h"
using namespace std;

namespace Ui {
class TaskInfo;
}

class TaskInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit TaskInfo(QWidget *parent = nullptr);
    ~TaskInfo();
    QFont font;
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;

public slots:
    void GetTaskData(QJsonObject *obj, const vector<QJsonObject> &categories, QTcpSocket *sock);

private slots:
    void on_EditButton_clicked();

private:
    Ui::TaskInfo *ui;
    QJsonObject currentTask;

};

#endif // TASKINFO_H
