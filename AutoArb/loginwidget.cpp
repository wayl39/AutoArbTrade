#include "loginwidget.h"
#include "ui_loginwidget.h"

#include "protocol.h"

#include <QMessageBox>

/**
 * @brief 构造函数
*/
LoginWidget::LoginWidget(QTcpSocket *socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    socket(socket)
{
    ui->setupUi(this);
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
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "提示", "账号或密码不能为空");
        return;
    }

    Protocol p(Protocol::regist);
    p["username"] = username;
    p["password"] = password;

    socket->write(p.pack());
}

/**
 * @brief 槽函数
*/
void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "提示", "账号或密码不能为空");
        return;
    }

    Protocol p(Protocol::login);
    p["type"] = "login";
    p["username"] = username;
    p["password"] = password;

    socket->write(p.pack());
}
