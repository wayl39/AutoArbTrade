#include "UserStrategyItem.h"
#include "ui_UserStrategyItem.h"

UserStrategyItem::UserStrategyItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserStrategyItem)
{
    ui->setupUi(this);
}

UserStrategyItem::~UserStrategyItem()
{
    delete ui;
}
