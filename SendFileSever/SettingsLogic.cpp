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
#include "RecvFile.h"
#include "protocol.h"
#include <QDir>
#include <QFileInfo>

SettingsLogic *SettingsLogic::GetInstance()
{
//    qDebug() << "服务器主线程：" << QThread::currentThread();
    static SettingsLogic instance;
    return &instance;
}

SettingsLogic::~SettingsLogic()
{

}

void SettingsLogic::init()
{
    initSetting();
}

void SettingsLogic::uninit()
{

}

void SettingsLogic::logProcFunc(const QVariantMap &dataMap, QVariantMap& responseMsg)
{
    QString username = dataMap.value(DefineFields::UserId).toString();
    QString password = dataMap.value(DefineFields::PassWord).toString();
    QString macAddress = dataMap.value(DefineFields::Mac).toString();
    if (getSettingValue(DefineFields::Admin_Account).toString() == username
            && SettingsLogic::GetInstance()->getSettingValue(DefineFields::Admin_Password).toString() == password){
        responseMsg.insert(MasterFileds::ret, MasterValues::ResponseResult::success);
        responseMsg.insert(MasterFileds::textDescribe, QString());
        responseMsg.insert(DefineFields::UserId, username);
        return;
    }
    QString ret, errorInfo;
    QStringList cliendIdList = m_settings->childGroups();
//    qDebug() << __FUNCTION__ << cliendIdList;
    if (!cliendIdList.contains(username)){
        ret = MasterValues::ResponseResult::fail;
        errorInfo = "没有此交易员账号，联系管理员添加";
    }
    m_settings->beginGroup(username);
    if (username != m_settings->value(DefineFields::UserId).toString()){
        ret = MasterValues::ResponseResult::fail;
        errorInfo = "账户填写错误";
    }
    if (password != m_settings->value(DefineFields::PassWord).toString()){
        ret = MasterValues::ResponseResult::fail;
        errorInfo = "密码填写错误";
    }
    if (macAddress != m_settings->value(DefineFields::Mac).toString()){
        ret = MasterValues::ResponseResult::fail;
        errorInfo = "MAC填写错误";
    }    
    m_settings->endGroup();
//    qDebug() << __FUNCTION__ << macAddress << getAllSettings();
    if (errorInfo.isEmpty()){
        ret = MasterValues::ResponseResult::success;
    }
    responseMsg.insert(MasterFileds::ret, ret);
    responseMsg.insert(MasterFileds::textDescribe, errorInfo);
    responseMsg.insert(DefineFields::UserId, username);
}

QVariant SettingsLogic::getSettingValue(const QString &key, const QVariant &defaultValue)
{
    return m_settings->value(key,defaultValue);
}

void SettingsLogic::setSettingValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

void SettingsLogic::writeSetting(const QVariantMap &dataMap, QVariantMap& responseMap)
{
    QString ret, errorInfo;
    responseMap = dataMap;
    if (FuncType::AddTrader == dataMap.value(DefineFields::funcType).toString()){
        QString cliendId = dataMap.value(DefineFields::UserId).toString();
        QStringList cliendIdList = m_settings->childGroups();
        if (cliendIdList.contains(cliendId)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此交易员账号已经添加，不能重复";
        } else{
            m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
            m_settings->setValue(DefineFields::UserId,dataMap.value(DefineFields::UserId).toString());
            m_settings->setValue(DefineFields::PassWord, dataMap.value(DefineFields::PassWord).toString());
            m_settings->setValue(DefineFields::Mac, dataMap.value(DefineFields::Mac).toString());
            m_settings->endGroup();
            ret = MasterValues::ResponseResult::success;
        }
        responseMap.insert(MasterFileds::ret, ret);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
    }
    else if (FuncType::AddFundAccount == dataMap.value(DefineFields::funcType).toString()){
        QString traderId = dataMap.value(DefineFields::UserId).toString();
        QString fundAccount = dataMap.value(DefineFields::FundAccount).toString();

        QStringList cliendIdList = m_settings->childGroups();
//        qDebug() << __FUNCTION__ << cliendIdList;
        if (!cliendIdList.contains(traderId)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此交易员账号不存在，请联系管理员添加";

            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QStringList fundList = m_settings->value(DefineFields::FundListStr).toStringList();
        if (fundList.contains(fundAccount)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此资金账户已经存在，不能重复添加";
            m_settings->endGroup();

            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        fundList.append(fundAccount);
        m_settings->setValue(DefineFields::FundListStr,fundList);
        m_settings->endGroup();
        ret = MasterValues::ResponseResult::success;
        responseMap.insert(MasterFileds::ret, ret);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
    }else if (FuncType::ReadTraderMsg == dataMap.value(DefineFields::funcType).toString()){
        QString cliendId = dataMap.value(DefineFields::UserId).toString();
        QStringList cliendIdList = m_settings->childGroups();
        if (!cliendIdList.contains(cliendId)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此交易员账号不存在，请联系管理员添加";
            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QStringList keys = m_settings->childKeys();
        foreach(auto key, keys){
            responseMap.insert(key, m_settings->value(key));
        }
        m_settings->endGroup();
        ret = MasterValues::ResponseResult::success;
        responseMap.insert(MasterFileds::ret, ret);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
    }
    else if (FuncType::ModifiTraderMsg == dataMap.value(DefineFields::funcType).toString()){
        QString traderId = dataMap.value(DefineFields::UserId).toString();

        QStringList cliendIdList = m_settings->childGroups();
        if (!cliendIdList.contains(traderId)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此交易员账号不存在，请联系管理员添加";
            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QString password = m_settings->value(DefineFields::PassWord).toString();
        QString mac = m_settings->value(DefineFields::Mac).toString();
        QStringList fundList = m_settings->value(DefineFields::FundListStr).toStringList();
        if (password != dataMap.value(DefineFields::PassWord).toString())
            m_settings->setValue(DefineFields::PassWord, dataMap.value(DefineFields::PassWord).toString());
        if (mac != dataMap.value(DefineFields::Mac).toString())
            m_settings->setValue(DefineFields::Mac, dataMap.value(DefineFields::Mac).toString());
        if (fundList != dataMap.value(DefineFields::FundListStr).toStringList())
            m_settings->setValue(DefineFields::FundListStr,dataMap.value(DefineFields::FundListStr).toStringList());

        m_settings->endGroup();
        ret = MasterValues::ResponseResult::success;
        responseMap.insert(MasterFileds::ret, ret);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
    }
}

void SettingsLogic::deleteSetting(const QVariantMap &dataMap, QVariantMap &responseMap)
{
    QString ret, errorInfo;
    responseMap = dataMap;
    if (FuncType::DeleteTrader == dataMap.value(DefineFields::funcType).toString()){
        QStringList cliendIdList = m_settings->childGroups();
        QString traderId = dataMap.value(DefineFields::UserId).toString();
        if (!cliendIdList.contains(traderId)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此交易员账号不存在，无法进行删除";
            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
        m_settings->remove("");
        m_settings->endGroup();
        ret = MasterValues::ResponseResult::success;
        responseMap.insert(MasterFileds::ret, ret);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
    }
    else if (FuncType::DeleteFundAccount == dataMap.value(DefineFields::funcType).toString()){
        QString traderId = dataMap.value(DefineFields::UserId).toString();
        QString fundAccount = dataMap.value(DefineFields::FundAccount).toString();

        QStringList cliendIdList = m_settings->childGroups();
        if (!cliendIdList.contains(traderId)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此交易员账号不存在，请重新填写";
            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QStringList fundList = m_settings->value(DefineFields::FundListStr).toStringList();
        if (!fundList.contains(fundAccount)){
            ret = MasterValues::ResponseResult::fail;
            errorInfo = "此资金账户不存在，无法删除";
            m_settings->endGroup();
            responseMap.insert(MasterFileds::ret, ret);
            responseMap.insert(MasterFileds::textDescribe, errorInfo);
            return;
        }
        fundList.removeOne(fundAccount);
        m_settings->setValue(DefineFields::FundListStr,fundList);

        m_settings->endGroup();
        ret = MasterValues::ResponseResult::success;
        responseMap.insert(MasterFileds::ret, ret);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
    }
}

void SettingsLogic::initSetting()
{
    QString fileName = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/work/" + "config.ini");
    m_settings = new QSettings(fileName,QSettings::IniFormat, this);
    m_settings->setAtomicSyncRequired(false);
    FileSystemWatcher::pInstance()->addWatchPath(fileName);
    connect(FileSystemWatcher::pInstance(), &FileSystemWatcher::signalFileChange, this, &SettingsLogic::slotWatcherFileChanged);
    QString path = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/log/");
    QDir dir(path);
    if (!dir.exists()){
        dir.mkpath(path);
    }
    // 设置管理员账号，密码
    CheckSettingValue(DefineFields::Admin_Account, "Admin");
    CheckSettingValue(DefineFields::Admin_Password, "123456");
    CheckSettingValue(DefineFields::Ip, "127.0.0.1");
    CheckSettingValue(DefineFields::Port, "8989");
    CheckSettingValue(DefineFields::Path, path);

    m_s = new QTcpServer(this);
    unsigned short port = m_settings->value(DefineFields::Port).toString().toUShort();
    m_s->listen(QHostAddress::Any, port);

    connect(m_s, &QTcpServer::newConnection, this, [=]{
        QTcpSocket* tcp = m_s->nextPendingConnection();
        qDebug() << QString("client new connect socket status: %1!").arg(tcp->isValid());

        /** @note 1. 管理套接字的读端 */
        connect(tcp, &QTcpSocket::readyRead, this, &SettingsLogic::slotOnReadyRead);

        /** @note 2. 管理套接字的断开 */
        connect(tcp, &QTcpSocket::disconnected, this, &SettingsLogic::slotDisconnected);

    });
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

    while((len = p.unpack(buffer)) > 0){
        QVariantMap responseMap;
        buffer = buffer.mid(len);
        QVariantMap dataMap = p.getData();
        qDebug() << __FUNCTION__ << p.getType() << ":" << dataMap;
        switch(p.getType()){
        case Protocol::none:
            break;
        case Protocol::login:
            logProcFunc(dataMap, responseMap);
            if (MasterValues::ResponseResult::success == responseMap.value(MasterFileds::ret).toString()
                    && getSettingValue(DefineFields::Admin_Account).toString() != dataMap.value(DefineFields::UserId).toString()){

            }
            break;
        case Protocol::settingFile:
            sendFileMsg(socket);
            break;
        case Protocol::addTrader:
        case Protocol::addAccount:
        case Protocol::modifiTraderMsg:
        case Protocol::readTraderMsg:
            writeSetting(dataMap, responseMap);
            break;
        case Protocol::deleteTrader:
        case Protocol::deleteAccount:
            deleteSetting(dataMap, responseMap);
            break;
        case Protocol::log:
            procLogFile(socket, dataMap, responseMap);
            break;
        default:
            break;
        }
        if (responseMap.isEmpty())
            continue;
        Protocol response(p.getType());
        response.setData(responseMap);
//        response.pack();
        socket->write(response.pack());
        qDebug() << __FUNCTION__ << response.getType() << " response:" << responseMap;
    }
}

void SettingsLogic::slotDisconnected()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    if (m_map.contains(socket))
        m_map.remove(socket);
    socket->close();
    socket->deleteLater();
}

void SettingsLogic::slotSendSettingFileEnd(const QVariantMap &dataMap)
{

}

void SettingsLogic::slotWatcherFileChanged(const QString &fileName)
{
    if (fileName == m_settings->fileName()){
        m_settings->sync();
    }
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

void SettingsLogic::sendFileMsg(QTcpSocket* socket)
{
    // 创建线程对象
    QThread* t = new QThread;
    // 创建任务对象
    SendFile* work = new SendFile(socket);

    work->moveToThread(t);

//    connect(this, &SettingsLogic::signalStartConnect, work, &SendFile::connectServer);

//    connect(work, &SendFile::signalConnectOk, this, [=]{
//        qDebug() << __FUNCTION__ << "成功连接服务器";
//    });

    connect(work, &SendFile::signalEnd, this, [=](const QVariantMap& dataMap){
        Protocol p(Protocol::settingFile);
        p.setData(dataMap);
        socket->write(p.pack());

        // 资源释放
        t->quit();
        t->wait();
        work->deleteLater();
        t->deleteLater();
    });

    connect(this, &SettingsLogic::signalSendFile, work, &SendFile::slotSendFile);

    t->start();

    QString filePath = m_settings->fileName();
    emit signalSendFile(filePath);
}

void SettingsLogic::procLogFile(QTcpSocket* socket, const QVariantMap &dataMap, QVariantMap &responseMap)
{
    m_map.insert(socket, dataMap.value(DefineFields::UserId).toString());
    m_settings->beginGroup(dataMap.value(DefineFields::UserId).toString());
    CheckSettingValue(DefineFields::Path+dataMap.value(DefineFields::UserId).toString(), getSettingValue(DefineFields::UserId).toString());
    QString fileName = m_settings->value(DefineFields::Path+dataMap.value(DefineFields::UserId).toString()).toString();
    m_settings->endGroup();
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists() && fileInfo.isFile()){
        QString path  = fileInfo.absoluteFilePath();
        QFile file(path);
        qint64 pos = 100;
        QByteArray tmp;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            while(!file.atEnd()){
                tmp = file.readAll();
                pos = file.pos();
            }
        }
        qDebug() << __FUNCTION__ << pos;
        file.close();
        QVariantMap logInfoMap;
        logInfoMap.insert(MasterValues::LogInfo::currentPos, pos);
        logInfoMap.insert(MasterValues::LogInfo::pathFileName, fileName);

        m_logInfoMap.insert(socket, logInfoMap);
        QString errorInfo;
        responseMap = logInfoMap;
        responseMap.insert(DefineFields::funcType, FuncType::Log);
        responseMap.insert(MasterFileds::ret, MasterValues::ResponseResult::success);
        responseMap.insert(MasterFileds::textDescribe, errorInfo);
        responseMap.insert(MasterValues::LogInfo::content, QString::fromStdString(tmp.toStdString()));
    }
}

void SettingsLogic::procLogFileChange()
{
    QString path = m_settings->value(DefineFields::Path).toString();
    qDebug() << __FUNCTION__ << path;
    if (path.isEmpty())
        return;
    QDir dir(path);
    QString filePath = dir.fromNativeSeparators(path);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Time);
    QStringList fileList = dir.entryList();
    QStringList dirFileList;
    foreach(auto fileName, fileList){
        dirFileList.append(QDir::fromNativeSeparators(filePath + "/" + fileName));
    }
    if (!dirFileList.isEmpty()){
        QString fileName = dirFileList.first();
        QFile* logFile = new QFile(fileName, this);
        QFileInfo fileInfo(*logFile);
        if (!logFile->open(QIODevice::ReadOnly| QIODevice::Text))
            return;

        QTextStream ts(logFile);
        QString text = ts.readAll();
        logFile->close();

        FileSystemWatcher::pInstance()->addWatchPath(fileName);

//        m_timer = new QTimer(this);
//        m_timer->start(5 * 1000);
//        connect(m_timer, &QTimer::timeout, this, &UserWindow::slotTimeOut);
    }
}

QVariantMap SettingsLogic::getAllSettings()
{
    QVariantMap msgMap;
    QStringList allKeys = m_settings->allKeys();
    foreach(auto key, allKeys){
        msgMap.insert(key, m_settings->value(key));
    }
    return msgMap;
}
