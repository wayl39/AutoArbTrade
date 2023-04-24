#include "SettingsLogic.h"
#include <QSettings>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include "DefineFields.h"
#include <QThread>
#include "SendFile.h"
#include "FileSystemWatcher.h"
#include "protocol.h"
#include <QHostAddress>

SettingsLogic *SettingsLogic::GetInstance()
{
    static SettingsLogic instance;
    return &instance;
}

SettingsLogic::~SettingsLogic()
{

}

void SettingsLogic::init()
{
    initSetting();
//    // 创建线程对象
//    QThread* t = new QThread;
//    // 创建任务对象
//    SendFile* work = new SendFile;

//    work->moveToThread(t);

//    connect(this, &SettingsLogic::signalStartConnect, work, &SendFile::connectServer);

//    connect(work, &SendFile::signalConnectOk, this, [=]{
//        qDebug() << __FUNCTION__ << "成功连接服务器";
//    });

//    connect(work, &SendFile::signalDisConnect, this, [=]{
//        // 资源释放
//        t->quit();
//        t->wait();
//        work->deleteLater();
//        t->deleteLater();
//    });

//    connect(this, &SettingsLogic::sendFile, work, &SendFile::sendFile);

//    t->start();

//    emit signalStartConnect(mSetting->value(DefineFields::Port).toString().toUShort(), mSetting->value(DefineFields::Ip).toString());

//    QString filePath = mSetting->fileName();
//    emit sendFile(filePath);

//    FileSystemWatcher::pInstance()->addWatchPath(filePath);
//    connect(FileSystemWatcher::pInstance(), &FileSystemWatcher::signalFileChange, this, &SettingsLogic::sendFile);
}

void SettingsLogic::uninit()
{

}

void SettingsLogic::logProcFunc(const QVariantMap &dataMap)
{
    Protocol p(Protocol::login);
    p.setData(dataMap);
    m_socket->write(p.pack());
}

QVariant SettingsLogic::getSettingValue(const QString &key, const QVariant &defaultValue)
{
    return m_settings->value(key,defaultValue);
}

void SettingsLogic::setSettingValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

void SettingsLogic::writeSetting(const QVariantMap &dataMap)
{
    if (FuncType::AddTrader == dataMap.value(DefineFields::funcType).toString()){
        Protocol p(Protocol::addTrader);
        p.setData(dataMap);
        m_socket->write(p.pack());
    }
    else if (FuncType::AddFundAccount == dataMap.value(DefineFields::funcType).toString()){
        Protocol p(Protocol::addAccount);
        p.setData(dataMap);
        m_socket->write(p.pack());
    }
    else if (FuncType::ModifiTraderMsg == dataMap.value(DefineFields::funcType).toString()){
        Protocol p(Protocol::modifiTraderMsg);
        p.setData(dataMap);
        m_socket->write(p.pack());
    }
}

void SettingsLogic::deleteSetting(const QVariantMap &dataMap, QString &errorInfo)
{
    if (FuncType::DeleteTrader == dataMap.value(DefineFields::funcType).toString()){
        Protocol p(Protocol::deleteTrader);
        p.setData(dataMap);
        m_socket->write(p.pack());
    }
    if (FuncType::DeleteFundAccount == dataMap.value(DefineFields::funcType).toString()){
        Protocol p(Protocol::deleteAccount);
        p.setData(dataMap);
        m_socket->write(p.pack());
    }
}

void SettingsLogic::initSetting()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/work/" + "config.ini";
    m_settings = new QSettings(fileName,QSettings::IniFormat, this);
    m_settings->clear();
    // 设置管理员账号，密码
    CheckSettingValue(DefineFields::Ip, "127.0.0.1");
    CheckSettingValue(DefineFields::Port, "8989");

    unsigned short port = m_settings->value(DefineFields::Port).toString().toUShort();
    QString ip = m_settings->value(DefineFields::Ip).toString();
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress(ip), port);

    if (m_socket->isValid()){
        createConnect();
    }
}

SettingsLogic::SettingsLogic()
{
    qDebug() << __FUNCTION__ << QThread::currentThread();
}

QSettings *SettingsLogic::getSetting() const
{
    return m_settings;
}

void SettingsLogic::setSetting(QSettings *setting)
{
    m_settings = setting;
}

void SettingsLogic::slotOnReadyRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray buffer = socket->readAll();

    Protocol p;
    int len = 0;
    QVariantMap responseMap;
    while((len = p.unpack(buffer)) > 0){
        buffer = buffer.mid(len);
        QVariantMap dataMap = p.getData();
        switch(p.getType()){
        case Protocol::none:
            break;
        case Protocol::login:
//            qDebug() << __FUNCTION__ << dataMap;
            emit signalResponseMsg(dataMap);
            break;
        case Protocol::addTrader:
            emit signalAddTraderRspMsg(dataMap);
            break;
        case Protocol::deleteTrader:
            emit signalDeleteTraderRspMsg(dataMap);
            break;

        case Protocol::addAccount:
            emit signalAddAccountRspMsg(dataMap);
            break;

        case Protocol::deleteAccount:
            emit signalDeleteAccountRspMsg(dataMap);
            break;

        case Protocol::modifiTraderMsg:
            emit signalModifTraderRspMsg(dataMap);
            break;
        default:
            break;
        }

    }
}

void SettingsLogic::slotDisconnected()
{
    m_socket->close();
    m_socket->deleteLater();
}

bool SettingsLogic::CheckSettingValue(const QString &key, const QVariant &defaultValue)
{
    QVariant varValue = m_settings->value(key);
    if (varValue.isNull()){
        varValue.setValue(defaultValue);
        m_settings->setValue(key, varValue);
        return false;
    }
    return true;
}

void SettingsLogic::createConnect()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &SettingsLogic::slotOnReadyRead);

    connect(m_socket, &QTcpSocket::disconnected, this, &SettingsLogic::slotDisconnected);
}
