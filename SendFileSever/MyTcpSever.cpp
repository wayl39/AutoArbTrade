#include "MyTcpSever.h"

MyTcpSever::MyTcpSever(QObject *parent) : QTcpServer(parent)
{

}

void MyTcpSever::incomingConnection(qintptr socketDescriptor)
{
    emit newDescriptor(socketDescriptor);
}
