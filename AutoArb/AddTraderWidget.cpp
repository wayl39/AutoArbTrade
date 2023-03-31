#include "AddTraderWidget.h"
#include "ui_AddTraderWidget.h"

AddTraderWidget::AddTraderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTraderWidget)
{
    ui->setupUi(this);
}

AddTraderWidget::~AddTraderWidget()
{
    delete ui;
}
