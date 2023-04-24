#include "SendFile.h"
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
#include <QThread>

SendFile::SendFile(QTcpSocket* tcp,QObject *parent) : QObject(parent)
{
    m_tcp = tcp;
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
