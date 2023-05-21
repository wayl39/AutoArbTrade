#ifndef SETTINGSLOGIC_H
#define SETTINGSLOGIC_H

#include <QObject>
#include <QVariantMap>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>

//Q_DECLARE_METATYPE(QVariant)

class QSettings;

class FileRowItem{
public:
    qint64 startPos = 0;
    QByteArray content;
    qint64 endPos = 0;
};

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

    void slotSendSettingFileEnd(const QVariantMap& dataMap);

    void slotWatcherFileChanged(const QString& fileName);

signals:
    void signalStartConnect(unsigned short port, QString ip);

    void signalSendFile(QString path);

private:

    void initSetting();

    bool CheckSettingValue(const QString& key, const QVariant &defaultValue);

    void sendFileMsg(QTcpSocket *socket);

    void procLogFile(QTcpSocket *socket, const QVariantMap& dataMap, QVariantMap &responseMap);

    void procLogFileChange(QTcpSocket* socket, const QVariantMap &dataMap);

    QVariantMap getAllSettings();

private:
    SettingsLogic();

    QSettings *m_settings{Q_NULLPTR};

    QTcpServer* m_s{Q_NULLPTR};

//    QTcpSocket* m_socket{Q_NULLPTR};
//    QMap<QTcpSocket*, QString> m_map;
    QMap<QTcpSocket*, QVariantMap> m_logInfoMap;
    QMap<QTcpSocket*, QTimer*> m_logTimerMap;
    QMap<QString, QSet<QTcpSocket*>> m_dicFile;
};

#endif // SETTINGSLOGIC_H
