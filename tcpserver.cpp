#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{

}

void TcpServer::open(const QHostAddress &addr, const quint16 port)
{
    pTcpServer = std::unique_ptr<QTcpServer>(new QTcpServer(this));

    connect(pTcpServer.get(), SIGNAL(newConnection()), this, SLOT(newUser()));

    if(!pTcpServer->listen(addr, port)){
        std::cout << "Unable to start the server: " << pTcpServer->errorString().constData() << std::endl;
        isListen = false;
    }
    else{
        std::cout << "Server start on: " << addr.toString().toStdString() << ":" << port << std::endl;
        isListen = true;
    }
}

void TcpServer::close()
{
    if(isListen){
        for(auto client : users){
            client->write("bye :'(");
            client->close();
        }

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
