#ifndef SETTINGSLOGIC_H
#define SETTINGSLOGIC_H

#include <QObject>
#include <QVariantMap>
#include <QTcpSocket>
//#include <QVariant>


//Q_DECLARE_METATYPE(QVariant)

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
    void logProcFunc(const QVariantMap& dataMap);

    QVariant getSettingValue(const QString& key, const QVariant &defaultValue = QVariant());
    void setSettingValue(const QString& key, const QVariant &value);

    void writeSetting(const QVariantMap& dataMap);

    void deleteSetting(const QVariantMap& dataMap);

    void modifiSetting(const QVariantMap& dataMap, QString& errorInfo);

    QSettings *getSetting() const;
    void setSetting(QSettings *setting);

signals:
    void signalResponseMsg(const QVariantMap& msgMap);
    void signalSettingFile(const QVariantMap& dataMap);
    void signalAddTraderRspMsg(const QVariantMap& msgMap);
    void signalDeleteTraderRspMsg(const QVariantMap& msgMap);
    void signalAddAccountRspMsg(const QVariantMap& msgMap);
    void signalDeleteAccountRspMsg(const QVariantMap& msgMap);
    void signalReadTraderRspMsg(const QVariantMap& msgMap);
    void signalModifTraderRspMsg(const QVariantMap& msgMap);
    void signalStartConnect(unsigned short port, QString ip);

    void sendFile(QString path);

private slots:
    void slotOnReadyRead();

    void slotDisconnected();

private:

    void initSetting();

    bool CheckSettingValue(const QString& key, const QVariant &defaultValue);

    void createConnect();

private:
    SettingsLogic();

    QSettings *m_settings{Q_NULLPTR};

    QTcpSocket* m_socket{Q_NULLPTR};

};

#endif // SETTINGSLOGIC_H
