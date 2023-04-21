#include "RecvFile.h"
#include <QFile>

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
        static qint64 count = 0;
        static qint64 total = 0;
        if (count == 0){
            m_tcp->read((char*)&total, 8);
        }

        // 读出剩余的数据
        QByteArray all = m_tcp->readAll();
        count += all.size();
        file->write(all);

        // 判断数据是否接收完成
        if (count == total){
            m_tcp->close();
            m_tcp->deleteLater();
            file->close();
            file->deleteLater();
            emit over();
        }
    });

    // 进入事件循环
    exec();
}
