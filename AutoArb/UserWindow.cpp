#include "UserWindow.h"
#include "ui_UserWindow.h"
#include "SettingsLogic.h"
#include "DefineFields.h"

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
