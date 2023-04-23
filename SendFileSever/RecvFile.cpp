#include "RecvFile.h"
#include <QFile>
#include "protocol.h"

RecvFile::RecvFile(QTcpSocket *tcp, QObject *parent)
    : QThread(parent),
    m_tcp(tcp)
{
    qDebug() << "服务器子线程：" << QThread::currentThread();
}

void RecvFile::run()
{
    QFile* file = new QFile("recv.txt");
    file->open(QFile::WriteOnly);

    // 接收数据
    connect(m_tcp, &QTcpSocket::readyRead, this, [=]{
        Protocol p;
//        m_tcp->read();
    });

    // 进入事件循环
    exec();
}
