#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class LoginWidget;
}

/**
 * @class LoginWidget
 * @brief 注册登录界面
*/
class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QTcpSocket* socket, QWidget *parent = 0);
    ~LoginWidget();

private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    Ui::LoginWidget *ui;

    QTcpSocket* socket;
};

#endif // LOGINWIDGET_H
