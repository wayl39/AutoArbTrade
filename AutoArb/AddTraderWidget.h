#ifndef ADDTRADERWIDGET_H
#define ADDTRADERWIDGET_H

#include <QWidget>

namespace Ui {
class AddTraderWidget;
}

class AddTraderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddTraderWidget(QWidget *parent = nullptr);
    ~AddTraderWidget();

public slots:
    void slotOkBtnClicked();

private:
    Ui::AddTraderWidget *ui;
};

#endif // ADDTRADERWIDGET_H
