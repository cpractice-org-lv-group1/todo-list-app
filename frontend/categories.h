#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QMainWindow>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <vector>
using namespace std;

namespace Ui {
class Categories;
}

class Categories : public QMainWindow
{
    Q_OBJECT

public:
    explicit Categories(QWidget *parent = nullptr);
    ~Categories();
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    QString CurrentCategory;
    vector<QJsonObject> categories;

signals:
    void ChangeCategory(QString category);

public slots:
    void GetCategoriesData(vector<QJsonObject> vect, QTcpSocket *sock, QString Category);
    void onItemSelected(QListWidgetItem* item);

private slots:
    void on_SetButton_clicked();

private:
    Ui::Categories *ui;
};

#endif // CATEGORIES_H