#include "UserWindow.h"
#include "ui_UserWindow.h"
#include "SettingsLogic.h"
#include "DefineFields.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDebug>

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
    delete ui;
}

void UserWindow::createWidget()
{
    setWindowTitle("交易管理系统(交易员)");
//    QStringList cliendIdList
    ui->menu_strategyManager->hide();
    ui->widget_strategy->hide();
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
    dir.setSorting(QDir::Name);
    dir.setNameFilters(QStringList("*.log"));
    QStringList fileList = dir.entryList();
    QStringList dirFileList;
    foreach(auto fileName, fileList){
        dirFileList.append(QDir::fromNativeSeparators(filePath + "/" + fileName));
    }
    ui->label_file->setText(dirFileList.join(";\n"));

    QFile outFile(dirFileList.first());
    outFile.open(QIODevice::ReadOnly);
    QTextStream ts(&outFile);

    ui->textBrowser_log->setText(ts.readAll());
    outFile.close();

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
