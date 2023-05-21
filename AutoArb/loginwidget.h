#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

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
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

public slots:
    void slotProcFunc(const QVariantMap& responseMsg);

signals:
    void signalLogSuccess(const QString& cliendId);

private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    void createWidget();
    void createConnect();
    QString getHostMacAddress();
private:
    Ui::LoginWidget *ui;


};

#endif // LOGINWIDGET_H
