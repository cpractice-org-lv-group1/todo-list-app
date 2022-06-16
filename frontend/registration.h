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
#include <QPixmap>
#include <QRegularExpression>

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
    QFont font;

signals:
    void mySignal(int id, QTcpSocket *sock);
    void ShowLogIn();
    void ShowSignUp();

private slots:
    void ChangeWin();
    void on_LoginButton_clicked();
    void on_GoToSign_clicked();
    void on_GoToLog_clicked();

    void on_SignUpButton_clicked();

    void on_SignUpBackButton_clicked();

public slots:
    void sockReady();
    void sockDisc();
    void ShowLogInSlot();
    void ShowSignUpSlot();

private:
    Ui::Registration *ui;
    Form *form;
};
#endif // REGISTRATION_H
