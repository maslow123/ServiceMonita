#include "websocket.h"

websocket::websocket(QObject *parent) : QObject(parent)
{
    cekStatus  = PATH_STATUS;
    process ->start(cekStatus);
    process ->waitForFinished();
    result = process ->readAllStandardOutput();
    list_result = result.split("\n");

    QJsonObject conf;
    conf["periode"] = 5000;
    conf["port"] = 2335;
    QJsonObject service;
        service["status"] = list_result.at(0);
        service["restart"] = "restart.sh";
        service["nama"] = "Monita_Service";
    QJsonArray listService;
        listService.append(service);
        service["status"] = list_result.at(0);
        service["restart"] = "restart2.sh";
        service["nama"] = "Monita_Service2";
        listService.append(service);
        conf["Service"] = listService;
    QJsonObject json;
        json["Config"] = conf;
    QJsonDocument jsonDoc(json);

    QFile loadFile(PATH_MONITA);
    QFile fileJson(PATH_JSON);
    QFile fileBin (PATH_BIN);
    if(!loadFile.exists()){
        QDir dir;
        dir.mkpath( PATH_MONITA);
        Q_ASSERT(fileJson.open(QFile::WriteOnly));
        Q_ASSERT(fileBin. open(QFile::WriteOnly));
        fileJson.write(jsonDoc.toJson());
        fileBin.write (jsonDoc.toBinaryData());
        fileJson.close();
        fileBin.close();
        Q_ASSERT(fileJson.open(QFile::ReadOnly));
        Q_ASSERT(fileBin. open(QFile::ReadOnly));

        QJsonDocument docJson =  QJsonDocument::fromJson(fileJson.readAll());
        QJsonDocument docBin  =  QJsonDocument::fromBinaryData(fileBin.readAll());

        qDebug()<<"Result 1 : "<<docJson<<endl;
        qDebug()<<"Result 2 : "<<docBin<<endl;

        m_pWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"), QWebSocketServer::NonSecureMode, this);
        if (m_pWebSocketServer->listen(QHostAddress::Any,conf["port"].toInt())) {
            connect(m_pWebSocketServer, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
    //        connect(m_pWebSocketServer, SIGNAL(closed()), this, SLOT(closed()));
        }
    }else{
        Q_ASSERT(fileJson.open(QFile::ReadOnly));
        Q_ASSERT(fileBin. open(QFile::ReadOnly));

        QJsonDocument docJson =  QJsonDocument::fromJson(fileJson.readAll());
        QJsonDocument docBin  =  QJsonDocument::fromBinaryData(fileBin.readAll());

        qDebug()<<docJson<<endl;
        qDebug()<<docBin<<endl;

        QString sConfig;
        fileJson.setFileName(PATH_JSON);
        Q_ASSERT(fileJson.open(QFile::ReadOnly));
        sConfig = fileJson.readAll();

        QJsonDocument config = QJsonDocument::fromJson(sConfig.toUtf8());
        QJsonObject jConfig = config.object();
        QJsonValue value = jConfig.value(QString("Config"));
        QJsonObject item = value.toObject();

        m_pWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"), QWebSocketServer::NonSecureMode, this);
        if (m_pWebSocketServer->listen(QHostAddress::Any,item["port"].toInt())){
            connect(m_pWebSocketServer, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
    //        connect(m_pWebSocketServer, SIGNAL(closed()), this, SLOT(closed()));
        }
    }
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(timer()));
    t->start(1000);
}
websocket::~websocket()
{
    if (m_pWebSocketServer->isListening()) {
        m_pWebSocketServer->close();
        qDeleteAll(m_clients.begin(), m_clients.end());
    }
}
void websocket::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &websocket::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &websocket::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &websocket::socketDisconnected);

    pSocket->ignoreSslErrors();

    m_clients << pSocket;
}
void websocket::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {pClient->sendTextMessage(message);}
    qDebug() <<message;
    for (int i = 0; i < m_clients.length(); i++) {
        m_clients.at(i)->sendTextMessage(message);
     }
}
void websocket::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {pClient->sendBinaryMessage(message);}
}
void websocket::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
void websocket::timer()
{
    QProcess *process = new QProcess();
    cekStatus  = PATH_STATUS;
    process ->start(cekStatus);
    process ->waitForFinished();
    result = process ->readAllStandardOutput();
    list_result = result.split("\n");
    QJsonObject service;
        service["Name"]   = "Monita_Service";
        service["Status"] =  list_result.at(0);
    QJsonArray ls;
        ls.append(service);
        service["Name"]   = "Monita_Service2";
        service["Status"] =  list_result.at(0);
        ls.append(service);
    QJsonObject conf;
         conf["Monita"] = ls;
         conf["Last Update"]= QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QJsonDocument jsonDoc(conf);
    for(int i=0; i< m_clients.length();i++){
         m_clients.at(i)->sendTextMessage(jsonDoc.toJson());
    }
}
