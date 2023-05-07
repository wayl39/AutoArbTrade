#include "UserWindow.h"
#include "ui_UserWindow.h"
#include "SettingsLogic.h"
#include "DefineFields.h"
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDebug>
#include "FileSystemWatcher.h"
#include <QDateTime>

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConncet();

//    requestLog();
}

UserWindow::~UserWindow()
{
    if (m_logFile){
        if (m_logFile->isOpen())
            m_logFile->close();
    }
    delete ui;
}

void UserWindow::createWidget()
{
    setWindowTitle("交易管理系统(交易员)");
//    QStringList cliendIdList

    ui->widget_strategy->hide();
    ui->menubar->removeAction(ui->action_addStragety);
    ui->menubar->removeAction(ui->action_deleteStragety);
    ui->menu_strategyManager->clear();
    ui->menu_strategyManager->setTitle("");
    ui->menu_log->clear();
    ui->menu_log->setTitle("");
    ui->widget_btn->hide();
}

void UserWindow::createLayout()
{

}

void UserWindow::createConncet()
{
    connect(ui->action_addStragety, &QAction::triggered, this, &UserWindow::slotAddStragetyClicked);
    connect(ui->action_deleteStragety, &QAction::triggered, this, &UserWindow::slotDeleteStragetyClicked);
    connect(ui->action_addRisk, &QAction::triggered, this, &UserWindow::slotAddRiskClicked);
    connect(ui->action_deleteRisk, &QAction::triggered, this, &UserWindow::slotDeleteRiskClicked);
    connect(ui->pb_dir, &QPushButton::clicked, this, [=]{
        getFileLog();
    });

    connect(SettingsLogic::GetInstance(), &SettingsLogic::signalLogRspMsg, this, &UserWindow::slotLogRspMsg);
}

void UserWindow::getFileLog()
{
    QString path = QFileDialog::getExistingDirectory(this, "open Log", QCoreApplication::applicationDirPath());
    qDebug() << __FUNCTION__ << path;
    if (path.isEmpty())
        return;
    QDir dir(path);
    QString filePath = dir.fromNativeSeparators(path);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Time);
    dir.setNameFilters(QStringList("*.log"));
    QStringList fileList = dir.entryList();
    QStringList dirFileList;
    foreach(auto fileName, fileList){
        dirFileList.append(QDir::fromNativeSeparators(filePath + "/" + fileName));
    }
//    ui->label_file->setText(dirFileList.join(";\n"));
    if (!dirFileList.isEmpty()){
        ui->label_file->setText(dirFileList.first());
        m_filePath = dirFileList.first();
        m_logFile = new QFile(m_filePath, this);
        m_fileInfo = QFileInfo(*m_logFile);
        m_passTime = m_fileInfo.lastModified();
        m_fileSize = m_fileInfo.size();
        if (!m_logFile->open(QIODevice::ReadOnly| QIODevice::Text))
            return;

        QTextStream ts(m_logFile);
        ui->textBrowser_log->setText(ts.readAll());
        m_logFile->close();

//        FileSystemWatcher::pInstance()->addWatchPath(m_filePath);
//        connect(FileSystemWatcher::pInstance(), &FileSystemWatcher::signalFileChange, this, &UserWindow::slotTimeOut);
        m_timer = new QTimer(this);
        m_timer->start(5 * 1000);
        connect(m_timer, &QTimer::timeout, this, &UserWindow::slotTimeOut);
    }
    if (m_logFile){
        connect(m_logFile, &QFile::readyRead, this, [=]{
            m_logFile->open(QIODevice::ReadWrite);
            QTextStream ts(m_logFile);
            ui->textBrowser_log->append(ts.readAll());
            m_logFile->close();
        });
    }

}

void UserWindow::requestLog()
{
    QVariantMap msgMap;
    msgMap.insert(DefineFields::funcType, FuncType::Log);
    msgMap.insert(DefineFields::UserId, m_clientId);
    SettingsLogic::GetInstance()->writeSetting(msgMap);
}

QString UserWindow::getFilePath() const
{
    return m_filePath;
}

void UserWindow::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

QString UserWindow::clientId() const
{
    return m_clientId;
}

void UserWindow::setClientId(const QString &clientId)
{
    m_clientId = clientId;
}

void UserWindow::slotAddStragetyClicked()
{

}

void UserWindow::slotDeleteStragetyClicked()
{

}

void UserWindow::slotAddRiskClicked()
{

}

void UserWindow::slotDeleteRiskClicked()
{

}

void UserWindow::slotLogRspMsg(const QVariantMap &dataMap)
{
    if (MasterValues::ResponseResult::success == dataMap.value(MasterFileds::ret).toString()){
        QString text = dataMap.value(MasterValues::LogInfo::content).toString();
        ui->textBrowser_log->append(text);
    }
}

void UserWindow::slotTimeOut()
{
//    qDebug() << __FUNCTION__ << m_fileInfo.size() << m_fileSize;
//    qDebug() << __FUNCTION__ << m_logFile->exists() << m_logFile->isOpen() << m_logFile->open(QIODevice::ReadOnly| QIODevice::Text);
//    ui->textBrowser_log->clear();
//    QFile file(m_filePath);
//    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QFileInfo fileInfo(*m_logFile);
    if (fileInfo.size() != m_fileSize){
        m_fileSize = fileInfo.size();
        if (m_logFile->exists() && !m_logFile->isOpen()){
            if (!m_logFile->open(QIODevice::ReadOnly| QIODevice::Text))
                return;
        }
//        qDebug() << __FUNCTION__ << 11;
//        qint64 cur = m_logFile->pos();
//        if (cur < m_fileInfo.size())
//            m_logFile->seek(cur);

//        QTextStream ts(m_logFile);
//        while(!ts.atEnd()){
//            ui->textBrowser_log->append(ts.readLine());
//        }

        QTextStream ts(m_logFile);
        ui->textBrowser_log->setText(ts.readAll());

        if (m_logFile->isOpen())
            m_logFile->close();
    }


}
