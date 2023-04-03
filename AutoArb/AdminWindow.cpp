#include "AdminWindow.h"
#include "ui_AdminWindow.h"
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include "ADialog.h"
#include "AddTraderWidget.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::slotAddTraderClicked()
{
    ADialog dialog("添加交易账号");
    AddTraderWidget widget;
    dialog.addWidget(&widget);
    connect(&dialog, &ADialog::accepted, &widget, &AddTraderWidget::slotOkBtnClicked);
    dialog.exec();
}

void AdminWindow::slotDeleteTraderClicked()
{

}

void AdminWindow::slotAddFundClicked()
{

}

void AdminWindow::slotDeleteFundClicked()
{

}

void AdminWindow::slotAddRiskClicked()
{

}

void AdminWindow::slotDeleteRiskClicked()
{

}

void AdminWindow::createWidget()
{
    setWindowTitle("交易管理系统（管理员）");
//    QMenu* menu_userManager = new QMenu("用户管理", this);
//    QAction* addTraderAction = new QAction("添加交易账户", menu_userManager);
//    QAction* deleteTraderAction = new QAction("删除交易账户", menu_userManager);
//    menu_userManager->addAction(addTraderAction);
//    menu_userManager->addAction(deleteTraderAction);
//    QMenu* menu_fundManager = new QMenu("资金账户管理", this);
//    QAction* addFundAction = new QAction("添加资金账户", menu_userManager);
//    QAction* deleteFundAction = new QAction("删除资金账户", menu_userManager);
//    menu_fundManager->addAction(addFundAction);
//    menu_fundManager->addAction(deleteFundAction);
//    ui->menubar->addMenu(menu_userManager);
//    ui->menubar->addMenu(menu_fundManager);
//    QMenu* menu_riskManager = new QMenu("风控管理", this);
//    QAction* addRiskAction = new QAction("添加风控指标", menu_userManager);
//    QAction* deleteRiskAction = new QAction("删除风控指标", menu_userManager);
//    menu_riskManager->addAction(addRiskAction);
//    menu_riskManager->addAction(deleteRiskAction);
//    ui->menubar->addMenu(menu_userManager);
//    ui->menubar->addMenu(menu_fundManager);
//    ui->menubar->addMenu(menu_riskManager);
}

void AdminWindow::createLayout()
{

}

void AdminWindow::createConnect()
{
    connect(ui->addTraderAction, &QAction::triggered, this, &AdminWindow::slotAddTraderClicked);
    connect(ui->deleteTraderAction, &QAction::triggered, this, &AdminWindow::slotDeleteTraderClicked);
    connect(ui->addFundAction, &QAction::triggered, this, &AdminWindow::slotAddFundClicked);
    connect(ui->deleteFundAction, &QAction::triggered, this, &AdminWindow::slotDeleteFundClicked);
    connect(ui->addRiskAction, &QAction::triggered, this, &AdminWindow::slotAddRiskClicked);
    connect(ui->deleteRiskAction, &QAction::triggered, this, &AdminWindow::slotDeleteRiskClicked);
}
