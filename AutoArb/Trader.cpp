#include "Trader.h"
#include "ui_Trader.h"

Trader::Trader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Trader)
{
    ui->setupUi(this);
}

Trader::~Trader()
{
    delete ui;
}
