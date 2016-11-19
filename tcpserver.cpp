#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    pTcpServer = std::unique_ptr<QTcpServer>(new QTcpServer(this));

    connect(pTcpServer.get(), SIGNAL(newConnection()), this, SLOT(newUser()));

    if(!pTcpServer->listen(QHostAddress::Any, 4444)){
        std::cout << "Unable to start the server: " << pTcpServer->errorString().constData() << std::endl;
        isListen = false;
    }
    else{
        isListen = true;
    }
}

void TcpServer::newUser()
{
    if(isListen){
        std::shared_ptr<QTcpSocket> client(pTcpServer->nextPendingConnection());

        connect(client.get(), SIGNAL(readyRead()), this, SLOT(newUser()));
        users.push_back(client);
    }
}

void TcpServer::readDataFromClient()
{
    std::unique_ptr<QTcpSocket> client(dynamic_cast<QTcpSocket*>(sender()));
    QString data(client->readAll());

    for(auto client : users){
        client->write(data.toUtf8());
    }
}
