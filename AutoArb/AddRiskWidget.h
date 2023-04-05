#ifndef ADDRISKWIDGET_H
#define ADDRISKWIDGET_H

#include <QWidget>

namespace Ui {
class AddRiskWidget;
}

class AddRiskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddRiskWidget(QWidget *parent = nullptr);
    ~AddRiskWidget();
private:
    void createWidget();
    void createLayout();
    void createConnect();
private:
    Ui::AddRiskWidget *ui;
};

#endif // ADDRISKWIDGET_H
