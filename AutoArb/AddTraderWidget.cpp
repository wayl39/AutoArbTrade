#include "AddTraderWidget.h"
#include "ui_AddTraderWidget.h"
#include <QVariantMap>
#include "DefineFields.h"
#include "SettingsLogic.h"

AddTraderWidget::AddTraderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTraderWidget)
{
    ui->setupUi(this);
}

AddTraderWidget::~AddTraderWidget()
{
    delete ui;
}

void AddTraderWidget::slotOkBtnClicked()
{
    QVariantMap dataMap;
    dataMap.insert(DefineFields::funcType, FuncType::AddTrader);
    dataMap.insert(DefineFields::UserId, ui->lineEdit_account->text());
    dataMap.insert(DefineFields::PassWord, ui->lineEdit_password->text());
    dataMap.insert(DefineFields::Mac, ui->lineEdit_mac->text());
    SettingsLogic::GetInstance()->writeSetting(dataMap);
}
