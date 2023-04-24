#include "AddTraderWidget.h"
#include "ui_AddTraderWidget.h"
#include <QVariantMap>
#include "DefineFields.h"
#include "SettingsLogic.h"
#include <QMessageBox>
#include <QValidator>

AddTraderWidget::AddTraderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTraderWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

AddTraderWidget::~AddTraderWidget()
{
    delete ui;
}

void AddTraderWidget::slotOkBtnClicked()
{
    QString errorInfo;
    checkUiData(errorInfo);
    if (!errorInfo.isEmpty()){
        QMessageBox::critical(this, "交易员添加", errorInfo);
        return;
    }

    QVariantMap dataMap;
    dataMap.insert(DefineFields::funcType, FuncType::AddTrader);
    dataMap.insert(DefineFields::UserId, ui->lineEdit_account->text());
    dataMap.insert(DefineFields::PassWord, ui->lineEdit_password->text());
    dataMap.insert(DefineFields::Mac, ui->lineEdit_mac->text());
    SettingsLogic::GetInstance()->writeSetting(dataMap);
//    if (!errorInfo.isEmpty()){
//        QMessageBox::critical(this, "添加交易员", errorInfo);
//        return;
//    }
//    emit signalBtnOkClicked(ui->lineEdit_account->text());
}

void AddTraderWidget::slotPVisibleBtnClicked()
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

void AddTraderWidget::createWidget()
{
    ui->pb_passwordVisible->setProperty("show", false);
    ui->pb_passwordVisible->setText("隐藏");
    // 密码输入框只能输入数字字母
    ui->lineEdit_password->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,}$")));
}

void AddTraderWidget::createLayout()
{

}

void AddTraderWidget::createConnect()
{
    connect(ui->pb_passwordVisible, &QPushButton::clicked, this, &AddTraderWidget::slotPVisibleBtnClicked);
}

void AddTraderWidget::checkUiData(QString &errorInfo)
{
    if (ui->lineEdit_account->text().isEmpty()){
        errorInfo  = "账号为空，请填写";
        return;
    }
    if (ui->lineEdit_password->text().isEmpty()){
        errorInfo  = "密码为空，请填写";
        return;
    }
    if (ui->lineEdit_mac->text().isEmpty()){
        errorInfo  = "Mac为空，请填写";
        return;
    }

    errorInfo = checkPassWordValide(ui->lineEdit_password->text());
//    if (errorInfo.isEmpty())
}

QString AddTraderWidget::checkPassWordValide(const QString &password)
{
    QString error;
//    if (password.length() > 20 || password.length() < 8){
//        error = "密码长度必需在8-20位之间";
//        return error;
//    }

    QRegExp regNumber("\\d");
    QRegExp regUpper("[A-Z]");
    QRegExp regLower("[a-z]");
    QRegExp regSpechars("[!@#$%^&*()]");

    int count = 0;
    if (password.contains(regNumber))
        count++;
    if (password.contains(regUpper))
        count++;
    if (password.contains(regLower))
        count++;

    if (count < 3){
        error = "密码必须是数字英文符号组合，包含大小写英文";
    }

    return error;
}
