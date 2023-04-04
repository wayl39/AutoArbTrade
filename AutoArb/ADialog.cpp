#include "ADialog.h"
#include "ui_ADialog.h"

ADialog::ADialog(const QString &title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
    connect(ui->pb_ok, &QPushButton::clicked, this, &ADialog::signalBtnOkClicked);
    connect(ui->pb_cancel, &QPushButton::clicked, this, &ADialog::signalBtnCancelClicked);
    connect(this, &ADialog::signalBtnCancelClicked, this, &ADialog::reject);
}

ADialog::~ADialog()
{
    delete ui;
}

void ADialog::addWidget(QWidget *widget)
{
    ui->horizontalLayout->addWidget(widget);
}
