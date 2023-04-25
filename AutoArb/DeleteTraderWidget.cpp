#include "DeleteTraderWidget.h"
#include "ui_DeleteTraderWidget.h"
#include <QMessageBox>
#include "DefineFields.h"
#include "SettingsLogic.h"

DeleteTraderWidget::DeleteTraderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteTraderWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

DeleteTraderWidget::~DeleteTraderWidget()
{
    delete ui;
}

void DeleteTraderWidget::slotOkBtnClicked()
{
    QString errorInfo;
    checkUiData(errorInfo);
    if (!errorInfo.isEmpty())
    {
        QMessageBox::critical(this, "交易员账户删除", errorInfo);
        return;
    }
    QVariantMap dataMap;
    dataMap.insert(DefineFields::funcType, FuncType::DeleteTrader);
    dataMap.insert(DefineFields::UserId, ui->lineEdit_account->text());
    SettingsLogic::GetInstance()->deleteSetting(dataMap);
    if (!errorInfo.isEmpty()){
        QMessageBox::critical(this, "交易员账户删除", errorInfo);
        return;
    }
    emit signalBtnOkClicked(ui->lineEdit_account->text());
}

void DeleteTraderWidget::createWidget()
{

}

void DeleteTraderWidget::createLayout()
{

}

void DeleteTraderWidget::createConnect()
{

}

void DeleteTraderWidget::checkUiData(QString &errorInfo)
{
    if (ui->lineEdit_account->text().isEmpty()){
        errorInfo  = "账号为空，请填写";
        return;
    }
}
