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

signals:
     void backSignal();

private slots:
    void on_pushButton_clicked();

public slots:
    void slot(int id, QTcpSocket *sock);
    void sockReady();
    void sockDisc();

private:
    Ui::Form *ui;
};

#endif // FORM_H
