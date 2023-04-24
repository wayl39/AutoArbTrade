#ifndef SETTINGSLOGIC_H
#define SETTINGSLOGIC_H

#include <QObject>
#include <QVariantMap>
#include <QTcpSocket>
#include <QTcpServer>


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
    void logProcFunc(const QVariantMap& dataMap, QVariantMap &responseMsg);

    QVariant getSettingValue(const QString& key, const QVariant &defaultValue = QVariant());
    void setSettingValue(const QString& key, const QVariant &value);

    void writeSetting(const QVariantMap& dataMap, QVariantMap &responseMap);

    void deleteSetting(const QVariantMap& dataMap, QVariantMap &responseMap);

    void modifiSetting(const QVariantMap& dataMap, QString& errorInfo);

    QSettings *getSetting() const;
    void setSetting(QSettings *setting);

public slots:
    void slotOnReadyRead();

    void slotDisconnected();

signals:
    void signalStartConnect(unsigned short port, QString ip);

    void sendFile(QString path);

private:

    void initSetting();

    bool CheckSettingValue(const QString& key, const QVariant &defaultValue);

    void sendMsg(const QVariantMap& msgMap, int type, QTcpSocket *socket);

private:
    SettingsLogic();

    QSettings *m_settings{Q_NULLPTR};

    QTcpServer* m_s{Q_NULLPTR};

//    QTcpSocket* m_socket{Q_NULLPTR};

};

#endif // SETTINGSLOGIC_H
