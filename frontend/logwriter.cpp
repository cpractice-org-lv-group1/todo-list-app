#include "logwriter.h"

LogWriter::LogWriter()
{

}

QString LogWriter::Send(const QString &data)
{
    QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return QString("[" + currenttime + "]" + " " + data + "\n");
}
