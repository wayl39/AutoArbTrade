#ifndef DELETEACCOUNTWIDGET_H
#define DELETEACCOUNTWIDGET_H

#include <QWidget>

namespace Ui {
class DeleteAccountWidget;
}

class DeleteAccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteAccountWidget(QWidget *parent = nullptr);
    ~DeleteAccountWidget();

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
    Ui::DeleteAccountWidget *ui;
};

#endif // DELETEACCOUNTWIDGET_H
