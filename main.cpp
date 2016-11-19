#include "tcpserver.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    TcpServer server;
    server.open("127.0.0.1", 4444);

    std::string command;
    while(true){
        std::cin >> command;
        if(command == "exit")
        {
            server.close();
            return;
        }
    }
    return a.exec();
}
