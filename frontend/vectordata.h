#ifndef VECTORDATA_H
#define VECTORDATA_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>
using namespace std;

class VectorData
{
public:
    VectorData();
    static vector<QJsonObject> Tasks;
    static vector<QJsonObject> Friends;
    static vector<QJsonObject> Categories;
    static QJsonObject User;
};



#endif // VECTORDATA_H
