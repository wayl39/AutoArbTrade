#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QNetworkInterface>
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

    createWidget();
    createConnect();
}

/**
 * @brief 析构函数
*/
LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::slotProcFunc(const QVariantMap &responseMsg)
{
    QString ret = responseMsg.value(MasterFileds::ret).toString();
    QString errorInfo = responseMsg.value(MasterFileds::textDescribe).toString();
    if (MasterValues::ResponseResult::success == ret){
        emit signalLogSuccess(responseMsg.value(DefineFields::UserId).toString());
    } else {
        ui->label_tip->setText(errorInfo);
    }
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
    msgMap.insert(DefineFields::funcType, FuncType::Login);
    msgMap.insert(DefineFields::UserId, username);
    msgMap.insert(DefineFields::PassWord, password);
    msgMap.insert(DefineFields::Mac, macAddress);
    SettingsLogic::GetInstance()->logProcFunc(msgMap);
}

void LoginWidget::createWidget()
{
    ui->btnRegister->hide();
//    ui->lineEdit_MacAddress->setReadOnly(true);
    ui->lineEdit_MacAddress->setText(getHostMacAddress());
}

void LoginWidget::createConnect()
{
    connect(SettingsLogic::GetInstance(), &SettingsLogic::signalResponseMsg, this, &LoginWidget::slotProcFunc);
}

QString LoginWidget::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
//    qDebug()<<nets;
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，且该mac的ip地址不能是回环地址并且是ipv4地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) &&
           nets[i].flags().testFlag(QNetworkInterface::IsRunning)
           && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            for (int j=0;j<nets[i].addressEntries().size() ;j++ ) {
            //该mac的ip地址不能为172.0.0.1，且需是ipv4地址
            if(nets[i].addressEntries().at(j).ip()!=QHostAddress::LocalHost&&nets[i].addressEntries().at(j).ip().protocol()== QAbstractSocket::IPv4Protocol
    ){
                    strMacAddr = nets[i].hardwareAddress();
                }
            }
        }
    }
//    qDebug()<<"strMacAddr"<<strMacAddr;
    return strMacAddr;
}

