#ifndef TRADER_H
#define TRADER_H

#include <QWidget>

namespace Ui {
class Trader;
}

class Trader : public QWidget
{
    Q_OBJECT

public:
    explicit Trader(QWidget *parent = nullptr);
    ~Trader();

private:
    Ui::Trader *ui;
};

#endif // TRADER_H
