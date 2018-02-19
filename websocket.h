#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include "config.h"
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets>
class websocket : public QObject
{
    Q_OBJECT
public:
    explicit websocket(QObject *parent = 0);
    ~websocket();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;

    QProcess *process = new QProcess();
    QString cekStatus;
    QString result;
    QStringList list_result;

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void timer();
Q_SIGNALS:
    void closed();
};

#endif // WEBSOCKET.H
