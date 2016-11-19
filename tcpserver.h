#pragma once
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <memory>
#include <iostream>

class TcpServer : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<QTcpServer> pTcpServer;
    bool isListen;
    std::vector<std::shared_ptr<QTcpSocket>> users;

public:
    explicit TcpServer(QObject *parent = 0);

signals:

public slots:
    void newUser();
    void readDataFromClient();
};

