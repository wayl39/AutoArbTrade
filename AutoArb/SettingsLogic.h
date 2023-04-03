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

    void writeSetting(const QVariantMap& dataMap);
private:

    void initSetting();
private:
    SettingsLogic();

    QSettings *mSetting{Q_NULLPTR};

};

#endif // SETTINGSLOGIC_H
