#include "AddStragetyWidget.h"
#include "ui_AddStragetyWidget.h"

AddStragetyWidget::AddStragetyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStragetyWidget)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

AddStragetyWidget::~AddStragetyWidget()
{
    delete ui;
}

void AddStragetyWidget::createWidget()
{

}

void AddStragetyWidget::createLayout()
{

}

void AddStragetyWidget::createConnect()
{

}
