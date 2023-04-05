#ifndef USERSTRATEGYITEM_H
#define USERSTRATEGYITEM_H

#include <QWidget>

namespace Ui {
class UserStrategyItem;
}

class UserStrategyItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserStrategyItem(QWidget *parent = nullptr);
    ~UserStrategyItem();

private:
    Ui::UserStrategyItem *ui;
};

#endif // USERSTRATEGYITEM_H
