#include "AddRiskWidget.h"
#include "ui_AddRiskWidget.h"

AddRiskWidget::AddRiskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRiskWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

AddRiskWidget::~AddRiskWidget()
{
    delete ui;
}

void AddRiskWidget::createWidget()
{

}

void AddRiskWidget::createLayout()
{

}

void AddRiskWidget::createConnect()
{

}
