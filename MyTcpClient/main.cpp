#include <QCoreApplication>
#include "mytcpclient.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    MyTcpClient client;
    std::string message;


    std::cout << "Кому?\n";
    std::cin >> message;
    client.sendString(message.c_str());
    std::cin >> message;
    client.sendString(message.c_str());

    return a.exec();
}

