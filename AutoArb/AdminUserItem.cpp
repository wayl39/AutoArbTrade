#include "AdminUserItem.h"
#include "ui_AdminUserItem.h"

AdminUserItem::AdminUserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminUserItem)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

AdminUserItem::~AdminUserItem()
{
    delete ui;
}

void AdminUserItem::setItemName(const QString &text)
{
//    ui->label_userId->setText(text);
    m_clientId = text;
}

void AdminUserItem::createWidget()
{

}

void AdminUserItem::createLayout()
{

}

void AdminUserItem::createConnect()
{
    connect(ui->pb_delete, &QPushButton::clicked, this, [=]{
        emit signalBtnDeleteClicked(m_clientId);
    });
    connect(ui->pb_modification, &QPushButton::clicked, this, [=]{
        emit signalBtnModifiClicked(m_clientId);
    });
}
