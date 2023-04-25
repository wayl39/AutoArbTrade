#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QTcpSocket *tcp, QObject *parent = nullptr);

    // 发送文件
    void slotSendFile(QString path);

signals:
//    void signalConnectOk();
    void signalEnd(const QVariantMap& dataMap);

//    void signalProcess(int percent);

public slots:

private:
    void createWidget();
    void createLayout();
    void createConnect();

private:
    QTcpSocket* m_tcp{Q_NULLPTR};
};

#endif // SENDFILE_H
