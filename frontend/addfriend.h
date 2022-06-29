#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <vector>
#include "operations.h"
using namespace std;

namespace Ui {
class AddFriend;
}

class AddFriend : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    ~AddFriend();
    QFont font;
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    int Id;

public slots:
    void GetToAddFriend(QTcpSocket *sock, int id);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
