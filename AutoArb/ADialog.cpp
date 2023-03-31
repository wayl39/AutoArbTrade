#include "ADialog.h"
#include "ui_ADialog.h"

ADialog::ADialog(const QString &title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
}

ADialog::~ADialog()
{
    delete ui;
}

void ADialog::addWidget(QWidget *widget)
{
    ui->horizontalLayout->addWidget(widget);
}
