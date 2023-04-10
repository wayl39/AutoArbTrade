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
//    qDebug() << __FUNCTION__ << cliendIdList;
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
    mSetting->endGroup();
    if (!errorInfo.isEmpty()){
        return;
    }
}

QVariant SettingsLogic::getSettingValue(const QString &key, const QVariant &defaultValue)
{
    return mSetting->value(key,defaultValue);
}

void SettingsLogic::setSettingValue(const QString &key, const QVariant &value)
{
    mSetting->setValue(key, value);
}

void SettingsLogic::writeSetting(const QVariantMap &dataMap, QString &errorInfo)
{
    if (FuncType::AddTrader == dataMap.value(DefineFields::funcType).toString()){
        QString cliendId = dataMap.value(DefineFields::UserId).toString();
        QStringList cliendIdList = mSetting->childGroups();
        if (cliendIdList.contains(cliendId)){
            errorInfo = "此交易员账号已经添加，不能重复";
            return;
        }
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        mSetting->setValue(DefineFields::UserId,dataMap.value(DefineFields::UserId).toString());
        mSetting->setValue(DefineFields::PassWord, dataMap.value(DefineFields::PassWord).toString());
        mSetting->setValue(DefineFields::Mac, dataMap.value(DefineFields::Mac).toString());
        mSetting->endGroup();
    }
    else if (FuncType::AddFundAccount == dataMap.value(DefineFields::funcType).toString()){
        QString traderId = dataMap.value(DefineFields::UserId).toString();
        QString fundAccount = dataMap.value(DefineFields::FundAccount).toString();

        QStringList cliendIdList = mSetting->childGroups();
        if (!cliendIdList.contains(traderId)){
            errorInfo = "此交易员账号不存在，请联系管理员添加";
            return;
        }
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QStringList fundList = mSetting->value(DefineFields::FundListStr).toStringList();
        if (fundList.contains(fundAccount)){
            errorInfo = "此资金账户已经存在，不能重复添加";
            mSetting->endGroup();
            return;
        }
        fundList.append(fundAccount);
        mSetting->setValue(DefineFields::FundListStr,fundList);

        mSetting->endGroup();
    }
    else if (FuncType::AddFundAccount == dataMap.value(DefineFields::funcType).toString()){
        QString traderId = dataMap.value(DefineFields::UserId).toString();

        QStringList cliendIdList = mSetting->childGroups();
        if (!cliendIdList.contains(traderId)){
            errorInfo = "此交易员账号不存在，请联系管理员添加";
            return;
        }
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QString password = mSetting->value(DefineFields::PassWord).toString();
        QString mac = mSetting->value(DefineFields::Mac).toString();
        QStringList fundList = mSetting->value(DefineFields::FundListStr).toStringList();
        if (password != dataMap.value(DefineFields::PassWord).toString())
            mSetting->setValue(DefineFields::PassWord, dataMap.value(DefineFields::PassWord).toString());
        if (mac != dataMap.value(DefineFields::Mac).toString())
            mSetting->setValue(DefineFields::Mac, dataMap.value(DefineFields::Mac).toString());
//        fundList.sort();
//        QStringList fundListTmp = dataMap.value(DefineFields::FundListStr).toStringList();
//        fundListTmp.sort();
        if (fundList != dataMap.value(DefineFields::FundListStr).toStringList())
            mSetting->setValue(DefineFields::FundListStr,fundList);

        mSetting->endGroup();
    }
}

void SettingsLogic::deleteSetting(const QVariantMap &dataMap, QString &errorInfo)
{
    if (FuncType::DeleteTrader == dataMap.value(DefineFields::funcType).toString()){
        QStringList cliendIdList = mSetting->childGroups();
        QString traderId = dataMap.value(DefineFields::UserId).toString();
        if (!cliendIdList.contains(traderId)){
            errorInfo = "此交易员账号不存在，无法进行删除";
            return;
        }
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        mSetting->remove("");
        mSetting->endGroup();
    }
    if (FuncType::DeleteFundAccount == dataMap.value(DefineFields::funcType).toString()){
        QString traderId = dataMap.value(DefineFields::UserId).toString();
        QString fundAccount = dataMap.value(DefineFields::FundAccount).toString();

        QStringList cliendIdList = mSetting->childGroups();
        if (!cliendIdList.contains(traderId)){
            errorInfo = "此交易员账号不存在，请重新填写";
            return;
        }
        mSetting->beginGroup(dataMap.value(DefineFields::UserId).toString());
        QStringList fundList = mSetting->value(DefineFields::FundListStr).toStringList();
        if (!fundList.contains(fundAccount)){
            errorInfo = "此资金账户不存在，无法删除";
            mSetting->endGroup();
            return;
        }
        fundList.removeOne(fundAccount);
        mSetting->setValue(DefineFields::FundListStr,fundList);

        mSetting->endGroup();
    }
}

void SettingsLogic::initSetting()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/work/" + "config.ini";
    mSetting = new QSettings(fileName,QSettings::IniFormat, this);
//    mSetting->clear();
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
