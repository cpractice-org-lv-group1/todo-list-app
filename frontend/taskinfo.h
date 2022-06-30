#ifndef TASKINFO_H
#define TASKINFO_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <vector>
#include <QMessageBox>
#include "operations.h"
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
    int currentpoints;
    int userpoints;

public slots:
    void GetTaskData(QJsonObject *obj, const vector<QJsonObject> &categories,QTcpSocket *sock, const int &points);

private slots:
    void on_EditButton_clicked();
    void on_DeleteButton_clicked();
    void on_DoneButton_clicked();
    void on_DoneButton_2_clicked();

private:
    Ui::TaskInfo *ui;
    QJsonObject currentTask;

};

#endif // TASKINFO_H
