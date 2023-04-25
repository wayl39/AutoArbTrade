#include "SendFile.h"
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
//#include <QThread>
#include "protocol.h"
#include <QSettings>

SendFile::SendFile(QTcpSocket* tcp,QObject *parent) : QObject(parent)
{
    m_tcp = tcp;
}

void SendFile::slotSendFile(QString path)
{
    qDebug() << __FUNCTION__ << path;
    QSettings* settings = new QSettings(path, QSettings::IniFormat);
    QStringList groups = settings->childGroups();
    QVariantMap protocolMap;
    foreach(QString group, groups){
        settings->beginGroup(group);
        QVariantMap valueMap;
        foreach (QString key,settings->childKeys()){
            valueMap.insert(key, settings->value(key));
        }
        settings->endGroup();
        protocolMap.insert(group, valueMap);
    }
    emit signalEnd(protocolMap);
//    QFile file(path);
//    QFileInfo info(path);
////    qint64 fileSize = info.size();

//    file.open(QFile::ReadOnly);
//    QByteArray data = file.readAll();
//    QStringList dataList = QString::fromStdString(data.toStdString()).split("\n");
//    QVariantMap protocolMap;
//    foreach(QString str, dataList){
//        if (str.startsWith("#"))
//            continue;
//        if (str.startsWith(";"))
//            continue;
//        if (str.startsWith("["))
//    }


//    while(!file.atEnd()){
//        static qint64 num = 0;
//        if (num == 0){
//            m_tcp->write((char*)&fileSize, 8);
//        }
//        QByteArray line = file.readLine();
//        num += line.size();
//        int precent = (num * 100 / fileSize);
//        emit signalProcess(precent);
//        m_tcp->write(line);
//    }
}
