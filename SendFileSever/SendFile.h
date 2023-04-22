#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    // 连接服务器
    void connectServer(unsigned short port, QString ip);
    // 发送文件
    void sendFile(QString path);

signals:
    void signalConnectOk();
    void signalDisConnect();

    void signalProcess(int percent);

public slots:

private:
    void createWidget();
    void createLayout();
    void createConnect();

private:
    QTcpSocket* m_tcp{Q_NULLPTR};
};

#endif // SENDFILE_H
