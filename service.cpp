#include "websocket.h"
service::service()
{

}
timer::timer()
{
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()),this,SLOT(time()));
    t->start(5000); // 5 second
}
void timer::time()
{
    QProcess *proses = new QProcess();
    QString cekStatus = PATH_CEK_STATUS;
    proses ->start(cekStatus);
    proses ->waitForFinished();
    QString result = proses ->readAllStandardOutput();
    QStringList list_result = result.split("\n");
    qDebug()<<list_result.at(0);
}
