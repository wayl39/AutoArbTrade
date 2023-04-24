#ifndef ADDACCOUNTWIDGET_H
#define ADDACCOUNTWIDGET_H

#include <QWidget>

namespace Ui {
class AddAccountWidget;
}

class AddAccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddAccountWidget(QWidget *parent = nullptr);
    ~AddAccountWidget();

signals:
    void signalBtnOkClicked();

public slots:
    void slotOkBtnClicked();

    void slotRspMsg(const QVariantMap& responseMap);

private:
    void createWidget();
    void createLayout();
    void createConnect();

    void checkUiData(QString &errorInfo);
private:
    Ui::AddAccountWidget *ui;
};

#endif // ADDACCOUNTWIDGET_H
