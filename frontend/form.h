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
#include "datafillhelper.h"
#include "vectordata.h"
#include "taskinfo.h"

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

    QJsonDocument doc;
    QJsonParseError docError;
    bool ifOpen;
    int Id;

signals:
     void backSignal();
     void SendTaskData(QJsonObject *obj, QTcpSocket *sock);

private slots:

    void on_SignOutButton_clicked();

    void on_ArchiveButton_clicked();

    void on_SearchOk_clicked();

public slots:
    void slot(int id, QTcpSocket *sock);
    void sockReady();
    void sockDisc();
    void onTaskClicked(QListWidgetItem* item);

private:
    Ui::Form *ui;
    TaskInfo *taskwindow;
};

#endif // FORM_H
