#ifndef DELETETRADERWIDGET_H
#define DELETETRADERWIDGET_H

#include <QWidget>

namespace Ui {
class DeleteTraderWidget;
}

class DeleteTraderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteTraderWidget(QWidget *parent = nullptr);
    ~DeleteTraderWidget();

signals:
    void signalBtnOkClicked(const QString& userId);

public slots:
    void slotOkBtnClicked();

    void slotRspMsg(const QVariantMap &responseMap);

private:
    void createWidget();
    void createLayout();
    void createConnect();

    void checkUiData(QString &errorInfo);

private:
    Ui::DeleteTraderWidget *ui;

};

#endif // DELETETRADERWIDGET_H
