#include "ModifiTraderWidget.h"
#include "ui_ModifiTraderWidget.h"
#include "DefineFields.h"
#include <QValidator>
#include "SettingsLogic.h"
#include <QMessageBox>

ModifiTraderWidget::ModifiTraderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifiTraderWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

ModifiTraderWidget::~ModifiTraderWidget()
{
    delete ui;
}

void ModifiTraderWidget::initUiData(const QVariantMap &dataMap)
{
    ui->lineEdit_account->setText(dataMap.value(DefineFields::UserId).toString());
    ui->lineEdit_password->setText(dataMap.value(DefineFields::PassWord).toString());
    ui->lineEdit_mac->setText(dataMap.value(DefineFields::Mac).toString());
//    ui->textEdit_account->setText(dataMap.value(DefineFields::FundListStr).toStringList().join("\n"));
}

void ModifiTraderWidget::slotOkBtnClicked()
{
    QVariantMap msgMap;
    msgMap.insert(DefineFields::funcType, FuncType::ModifiTraderMsg);
    msgMap.insert(DefineFields::UserId, ui->lineEdit_account->text());
    msgMap.insert(DefineFields::PassWord, ui->lineEdit_password->text());
    msgMap.insert(DefineFields::Mac, ui->lineEdit_mac->text());
//    msgMap.insert(DefineFields::FundListStr, ui->textEdit_account->toPlainText().split("\n"));
    qDebug() << __FUNCTION__ << ui->textEdit_account->toPlainText();
    SettingsLogic::GetInstance()->writeSetting(msgMap);
//    QMessageBox::critical(this, "修改交易员信息", "1111");
//    emit signalBtnOkClicked();
}

void ModifiTraderWidget::slotPVisibleBtnClicked()
{
    if (QLineEdit::Password == ui->lineEdit_password->echoMode()){
        ui->pb_passwordVisible->setProperty("show", true);
        ui->pb_passwordVisible->setText("显示");
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    } else {
        ui->pb_passwordVisible->setProperty("show", false);
        ui->pb_passwordVisible->setText("隐藏");
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
}

void ModifiTraderWidget::slotModifTraderRspMsg(const QVariantMap &dataMap)
{
    qDebug() << __FUNCTION__ << dataMap;
    QString ret = dataMap.value(MasterFileds::ret).toString();
    QString errorInfo = dataMap.value(MasterFileds::textDescribe).toString();
    QString trader = dataMap.value(DefineFields::UserId).toString();
    if (MasterValues::ResponseResult::success == ret){
        emit signalBtnOkClicked();
    } else {
        if (!errorInfo.isEmpty()){
            QMessageBox::critical(this, "修改交易员信息", errorInfo);
            return;
        }
    }
}

void ModifiTraderWidget::createWidget()
{
    ui->lineEdit_account->setEnabled(false);
    ui->pb_passwordVisible->setProperty("show", false);
    ui->pb_passwordVisible->setText("隐藏");
    // 密码输入框只能输入数字字母
    ui->lineEdit_password->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,}$")));
}

void ModifiTraderWidget::createLayout()
{

}

void ModifiTraderWidget::createConnect()
{
    connect(ui->pb_passwordVisible, &QPushButton::clicked, this, &ModifiTraderWidget::slotPVisibleBtnClicked);
    connect(SettingsLogic::GetInstance(), &SettingsLogic::signalModifTraderRspMsg, this, &ModifiTraderWidget::slotModifTraderRspMsg);
}
