#include "SettingsLogic.h"
#include <QSettings>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include "DefineFields.h"

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
}

void SettingsLogic::uninit()
{

}

void SettingsLogic::logProcFunc(const QVariantMap &dataMap, QString &errorInfo)
{
    QString username = dataMap.value(DefineFields::UserId).toString();
    QString password = dataMap.value(DefineFields::PassWord).toString();
    QString macAddress = dataMap.value(DefineFields::Mac).toString();
    if (getSettingValue(DefineFields::Admin_Account).toString() == username
            && SettingsLogic::GetInstance()->getSettingValue(DefineFields::Admin_Password).toString() == password){
        return;
    }
    QStringList cliendIdList = mSetting->childGroups();
    if (!cliendIdList.contains(username)){
        errorInfo = "没有此交易员账号，联系管理员添加";
        return;
    }
    mSetting->beginGroup(username);
    if (username != mSetting->value(DefineFields::UserId).toString()){
        errorInfo = "账户填写错误";
    }
    if (password != mSetting->value(DefineFields::PassWord).toString()){
        errorInfo = "密码填写错误";
    }
    if (macAddress != mSetting->value(DefineFields::Mac).toString()){
        errorInfo = "MAC填写错误";
    }
    if (!errorInfo.isEmpty())
        return;
    mSetting->endGroup();
}

QVariant SettingsLogic::getSettingValue(const QString &key, const QVariant &defaultValue)
{
    return mSetting->value(key,defaultValue);
}

void SettingsLogic::setSettingValue(const QString &key, const QVariant &value)
{
    mSetting->setValue(key, value);
}

void SettingsLogic::writeSetting(const QVariantMap &dataMap)
{
    if (FuncType::AddTrader == dataMap.value(DefineFields::funcType).toString()){
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        mSetting->setValue(DefineFields::UserId,dataMap.value(DefineFields::UserId).toString());
        mSetting->setValue(DefineFields::PassWord, dataMap.value(DefineFields::PassWord).toString());
        mSetting->setValue(DefineFields::Mac, dataMap.value(DefineFields::Mac).toString());
        mSetting->endGroup();
    }
}

void SettingsLogic::deleteSetting(const QVariantMap &dataMap)
{
    if (FuncType::DeleteTrader == dataMap.value(DefineFields::funcType).toString()){
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        mSetting->remove("");
        mSetting->endGroup();
    }
}

void SettingsLogic::initSetting()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/work/" + "config.ini";
    mSetting = new QSettings(fileName,QSettings::IniFormat, this);
    mSetting->clear();
    // 设置管理员账号，密码
    mSetting->setValue(DefineFields::Admin_Account, "Admin");
    mSetting->setValue(DefineFields::Admin_Password, "123456");
}

SettingsLogic::SettingsLogic()
{

}

QSettings *SettingsLogic::getSetting() const
{
    return mSetting;
}

void SettingsLogic::setSetting(QSettings *setting)
{
    mSetting = setting;
}
