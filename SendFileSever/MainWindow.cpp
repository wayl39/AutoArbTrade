#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RecvFile.h"

#include <qmessagebox.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("服务器");

    qDebug() << "服务器主线程：" << QThread::currentThread();
    m_s = new QTcpServer(this);

    connect(ui->pb_start, &QPushButton::clicked, this, [=]{
        unsigned short port = ui->le_port->text().toUShort();
        m_s->listen(QHostAddress::Any, port);
        ui->pb_start->setDisabled(true);
    });

    connect(m_s, &QTcpServer::newConnection, this, [=]{
        QTcpSocket* tcp = m_s->nextPendingConnection();

        // 创建子线程
        RecvFile* subThread = new RecvFile(tcp);
        subThread->start();

        connect(subThread, &RecvFile::over, this, [=]{
            subThread->exit();
            subThread->wait();
            subThread->deleteLater();
            QMessageBox::information(this, "文件接收", "文件接收完成");
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
