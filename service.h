#ifndef SERVICE_H
#define SERVICE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QObject>

class service
{
public:
    service();
    QProcess *process = new QProcess();
    QString cekStatus;
    QString result;
    QStringList list_result;
};

#endif // SERVICE_H
