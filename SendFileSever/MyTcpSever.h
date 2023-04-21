#ifndef MYTCPSEVER_H
#define MYTCPSEVER_H

#include <QTcpServer>

class MyTcpSever : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpSever(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor);
signals:
    void newDescriptor(qintptr socketDescriptor);
public slots:
};

#endif // MYTCPSEVER_H
