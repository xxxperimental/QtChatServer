#include "tcpserver.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    TcpServer server;
    server.open(QHostAddress("127.0.0.1"), 4444);

    return a.exec();
}
