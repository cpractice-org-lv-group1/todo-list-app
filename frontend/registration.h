#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include <form.h>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    Registration(QWidget *parent = nullptr);
    ~Registration();

    QTcpSocket* socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;
    bool ifOpen;
    int Id;

signals:
    void mySignal(int id, QTcpSocket *sock);

private slots:
    void on_pushButton_clicked();
    void ChangeWin();

public slots:
    void sockReady();
    void sockDisc();

private:
    Ui::Registration *ui;
    Form *form;
};
#endif // REGISTRATION_H
