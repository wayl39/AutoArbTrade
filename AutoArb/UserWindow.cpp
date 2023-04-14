#include "UserWindow.h"
#include "ui_UserWindow.h"
#include "SettingsLogic.h"
#include "DefineFields.h"
//#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDebug>
#include "FileSystemWatcher.h"

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConncet();
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
        QString m_filePath = dirFileList.first();
        m_logFile = new QFile(m_filePath);
        m_fileSize = m_logFile->size();
        if (!m_logFile->open(QIODevice::ReadOnly| QIODevice::Text))
            return;

        QTextStream ts(m_logFile);
        ui->textBrowser_log->setText(ts.readAll());
        m_logFile->close();

        FileSystemWatcher::addWatchPath(m_filePath);
//        m_timer = new QTimer(this);
//        m_timer->start(10 * 1000);
//        connect(m_timer, &QTimer::timeout, this, &UserWindow::slotTimeOut);
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

void UserWindow::slotTimeOut()
{
    qDebug() << __FUNCTION__ ;
    if (m_logFile->exists() && !m_logFile->isOpen()){
        if (!m_logFile->open(QIODevice::ReadOnly| QIODevice::Text))
            return;
    }
    if (m_logFile->size() != m_fileSize){
        QTextStream ts(m_logFile);
        ui->textBrowser_log->setText(ts.readAll());
        if (m_logFile->isOpen())
            m_logFile->close();
    }

}
