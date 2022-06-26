#ifndef ADDTASK_H
#define ADDTASK_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <vector>
using namespace std;

namespace Ui {
class AddTask;
}

class AddTask : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr);
    ~AddTask();
    QFont font;
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    int Id;

public slots:
    void GetToAddTask(QTcpSocket *sock, int id, const vector<QJsonObject> &categories);

private slots:
    void on_AddButton_clicked();

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H
