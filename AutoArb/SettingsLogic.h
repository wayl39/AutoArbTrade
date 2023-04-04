#ifndef SETTINGSLOGIC_H
#define SETTINGSLOGIC_H

#include <QObject>
#include <QVariantMap>

#define BISADMIN 1

class QSettings;

class SettingsLogic : public QObject
{
    Q_OBJECT
public:
    static SettingsLogic *GetInstance();
    ~SettingsLogic();
    void init();
    void uninit();

    // 验证Log
    void logProcFunc(const QVariantMap& dataMap, QString& errorInfo);

    QVariant getSettingValue(const QString& key, const QVariant &defaultValue = QVariant());
    void setSettingValue(const QString& key, const QVariant &value);

    void writeSetting(const QVariantMap& dataMap);

    void deleteSetting(const QVariantMap& dataMap);

    QSettings *getSetting() const;
    void setSetting(QSettings *setting);

private:

    void initSetting();
private:
    SettingsLogic();

    QSettings *mSetting{Q_NULLPTR};

};

#endif // SETTINGSLOGIC_H
