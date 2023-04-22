#include "SendFile.h"
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
#include <QThread>

SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

void SendFile::connectServer(unsigned short port, QString ip)
{
    qDebug() << "客户端子线程：" << QThread::currentThread();
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip), port);

    connect(m_tcp, &QTcpSocket::connected, this, &SendFile::signalConnectOk);
    connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
        m_tcp->close();
        m_tcp->deleteLater();
        emit signalDisConnect();
    });
}

void SendFile::sendFile(QString path)
{
    qDebug() << __FUNCTION__ << path;
    QFile file(path);
    QFileInfo info(path);
//    qint64 fileSize = info.size();

    file.open(QFile::ReadOnly);

    while(!file.atEnd()){
//        static qint64 num = 0;
//        if (num == 0){
//            m_tcp->write((char*)&fileSize, 8);
//        }
        QByteArray line = file.readLine();
//        num += line.size();
//        int precent = (num * 100 / fileSize);
//        emit signalProcess(precent);
        m_tcp->write(line);
    }
}
