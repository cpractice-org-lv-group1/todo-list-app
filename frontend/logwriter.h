#ifndef LOGWRITER_H
#define LOGWRITER_H
#include <QString>
#include <QDateTime>

class LogWriter
{
public:
    LogWriter();
    static QString Send(QString data);
};

#endif // LOGWRITER_H
