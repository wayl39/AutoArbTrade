#include "DeleteAccountWidget.h"
#include "ui_DeleteAccountWidget.h"
#include "SettingsLogic.h"
#include "DefineFields.h"
#include <QMessageBox>

DeleteAccountWidget::DeleteAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteAccountWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

DeleteAccountWidget::~DeleteAccountWidget()
{
    delete ui;
}

void DeleteAccountWidget::slotOkBtnClicked()
{
    QString errorInfo;
    checkUiData(errorInfo);
    if (!errorInfo.isEmpty()){
        QMessageBox::critical(this, "资金账户删除", errorInfo);
        return;
    }

    QVariantMap dataMap;
    dataMap.insert(DefineFields::funcType, FuncType::DeleteFundAccount);
    dataMap.insert(DefineFields::UserId, ui->lineEdit_traderAccount->text());
    dataMap.insert(DefineFields::FundAccount, ui->lineEdit_fundAccount->text());
    SettingsLogic::GetInstance()->deleteSetting(dataMap);
    if (!errorInfo.isEmpty()){
        QMessageBox::critical(this, "资金账户删除", errorInfo);
        return;
    }
    emit signalBtnOkClicked();
}

void DeleteAccountWidget::createWidget()
{

}

void DeleteAccountWidget::createLayout()
{

}

void DeleteAccountWidget::createConnect()
{
}

void DeleteAccountWidget::checkUiData(QString &errorInfo)
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
