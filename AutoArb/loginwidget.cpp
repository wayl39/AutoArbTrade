#include "loginwidget.h"
#include "ui_loginwidget.h"

#include "protocol.h"
#include "SettingsLogic.h"
#include "DefineFields.h"
#include <QSettings>
#include <QMessageBox>

/**
 * @brief 构造函数
*/
LoginWidget::LoginWidget(QWidget *parent)
    : QWidget (parent),
      ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->btnRegister->hide();
}

/**
 * @brief 析构函数
*/
LoginWidget::~LoginWidget()
{
    delete ui;
}

/**
 * @brief 槽函数
*/
void LoginWidget::on_btnRegister_clicked()
{
//    QString username = ui->leUsername->text();
//    QString password = ui->lePassword->text();

//    if(username.isEmpty() || password.isEmpty()){
//        QMessageBox::warning(this, "提示", "账号或密码不能为空");
//        return;
//    }

//    Protocol p(Protocol::regist);
//    p["username"] = username;
//    p["password"] = password;

//    socket->write(p.pack());
}

/**
 * @brief 槽函数
*/
void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->lineEdit_Username->text();
    QString password = ui->lineEdit_Password->text();
    QString macAddress = ui->lineEdit_MacAddress->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "提示", "账号或密码不能为空");
        return;
    }
    QVariantMap msgMap;
    msgMap.insert(DefineFields::funcType, FuncType::Log);
    msgMap.insert(DefineFields::UserId, username);
    msgMap.insert(DefineFields::PassWord, password);
    msgMap.insert(DefineFields::Mac, macAddress);
    QString errorInfo;
    SettingsLogic::GetInstance()->logProcFunc(msgMap, errorInfo);
    if (errorInfo.isEmpty()){
        emit signalLogSuccess(username);
    } else {
        ui->label_tip->setText(errorInfo);
    }
//    if (cliendIdList.contains())
}
