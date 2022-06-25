#ifndef FORM_H
#define FORM_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "operations.h"
#include <vector>
#include <QFile>
#include <QInputDialog>
#include <QDialogButtonBox>
#include "datafillhelper.h"
#include "vectordata.h"
#include "taskinfo.h"
#include "logwriter.h"
#include "categories.h"
#include "friendinfo.h"

namespace Ui {
class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    QTcpSocket* socket;
    QByteArray Data;
    QFont font;

    QJsonDocument doc;
    QJsonParseError docError;
    bool ifOpen;
    int Id;
    QFile log;
    QTextStream logstream;
    QFile hoursSearch;
    QTextStream streamSearch;
    int hours;
    QString CurrentCategory;

signals:
     void backSignal();
     void SendTaskData(QJsonObject *obj, vector<QJsonObject> categories,QTcpSocket *sock);
     void SendFriendData(QJsonObject *obj, QTcpSocket *sock);
     void SendCategoriesData(vector<QJsonObject> vect, QTcpSocket *sock, QString Category);

private slots:

    void on_SignOutButton_clicked();
    void on_ArchiveButton_clicked();
    void on_SearchOk_clicked();
    void on_CategoriesButton_clicked();
    void on_FriendRequests_clicked();

    void on_AddFriendButton_clicked();

public slots:
    void slot(int id, QTcpSocket *sock, QTextStream *sendlogstream);
    void sockReady();
    void sockDisc();
    void onTaskClicked(QListWidgetItem* item);
    void onFriendClicked(QListWidgetItem* item);
    void GetChangedCategory(QString category);

private:
    Ui::Form *ui;
    TaskInfo *taskwindow;
    Categories *categorywindow;
    FriendInfo *friendwindow;
};

#endif // FORM_H
