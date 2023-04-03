#include "SettingsLogic.h"
#include <QSettings>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>

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
