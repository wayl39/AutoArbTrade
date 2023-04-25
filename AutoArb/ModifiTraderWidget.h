#ifndef MODIFITRADERWIDGET_H
#define MODIFITRADERWIDGET_H

#include <QWidget>

namespace Ui {
class ModifiTraderWidget;
}

class ModifiTraderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifiTraderWidget(QWidget *parent = nullptr);
    ~ModifiTraderWidget();

    void initUiData(const QVariantMap& dataMap);

signals:
    void signalBtnOkClicked();

public slots:
    void slotOkBtnClicked();

    void slotPVisibleBtnClicked();

    void slotModifTraderRspMsg(const QVariantMap& dataMap);

private:
    void createWidget();
    void createLayout();
    void createConnect();
private:
    Ui::ModifiTraderWidget *ui;
};

#endif // MODIFITRADERWIDGET_H
