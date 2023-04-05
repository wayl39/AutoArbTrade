#include "AddAccountWidget.h"
#include "ui_AddAccountWidget.h"
#include "SettingsLogic.h"
#include "DefineFields.h"
#include <QMessageBox>

AddAccountWidget::AddAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAccountWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

AddAccountWidget::~AddAccountWidget()
{
    delete ui;
}

void AddAccountWidget::slotOkBtnClicked()
{
    QString errorInfo;
    checkUiData(errorInfo);
    if (!errorInfo.isEmpty()){
        QMessageBox::critical(this, "添加资金账户", errorInfo);
        return;
    }

    QVariantMap dataMap;
    dataMap.insert(DefineFields::funcType, FuncType::AddFundAccount);
    dataMap.insert(DefineFields::UserId, ui->lineEdit_traderAccount->text());
    dataMap.insert(DefineFields::FundAccount, ui->lineEdit_fundAccount->text());
    SettingsLogic::GetInstance()->writeSetting(dataMap, errorInfo);
    if (!errorInfo.isEmpty()){
        QMessageBox::critical(this, "添加资金账户", errorInfo);
        return;
    }
    emit signalBtnOkClicked();
}

void AddAccountWidget::createWidget()
{

}

void AddAccountWidget::createLayout()
{

}

void AddAccountWidget::createConnect()
{

}

void AddAccountWidget::checkUiData(QString &errorInfo)
{
    if (ui->lineEdit_fundAccount->text().isEmpty()){
        errorInfo = "资金账号为空，请填写";
        return;
    }

    if (ui->lineEdit_traderAccount->text().isEmpty())
    {
        errorInfo = "交易员账号为空，请填写";
        return;
    }
}
