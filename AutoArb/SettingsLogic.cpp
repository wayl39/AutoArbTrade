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

void SettingsLogic::initSetting()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/work/" + "config.ini";
//    if (fileName.i)
    QFile file(fileName);
    mSetting = new QSettings(fileName,QSettings::IniFormat, this);
    mSetting->setValue("my", "123");
    qDebug() << __FUNCTION__ << file.fileName() << fileName;
}

SettingsLogic::SettingsLogic()
{

}
