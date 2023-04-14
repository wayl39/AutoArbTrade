#include "AdminWindow.h"
#include "ui_AdminWindow.h"
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include "ADialog.h"
#include "AddTraderWidget.h"
#include "AddAccountWidget.h"
#include "SettingsLogic.h"
#include <QSettings>
#include "AdminUserItem.h"
#include "DeleteTraderWidget.h"
#include "DeleteAccountWidget.h"
#include <QDebug>
#include "SettingsLogic.h"
#include "DefineFields.h"
#include <QMessageBox>
#include "ModifiTraderWidget.h"

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

void AdminWindow::slotAddTraderSuccess(const QString &cliendId)
{
    QListWidgetItem* item = new QListWidgetItem(cliendId);
    AdminUserItem *widget = new AdminUserItem;
//    item->setText(cliendId);
    widget->setItemName(cliendId);
    item->setSizeHint(QSize(200, 40));
    ui->listWidget_trader->addItem(item);
    ui->listWidget_trader->setItemWidget(item, widget);
    connect(widget, &AdminUserItem::signalBtnDeleteClicked, this, &AdminWindow::slotBtnDeleteClicked);

    connect(widget, &AdminUserItem::signalBtnModifiClicked, this, &AdminWindow::slotBtnModifiClicked);
}

void AdminWindow::slotDeleteTraderSuccess(const QString &cliendId)
{

//    int count = ui->listWidget_trader->count();
    QList<QListWidgetItem*> findItems = ui->listWidget_trader->findItems(cliendId, Qt::MatchExactly);
    qDebug() << __FUNCTION__ << cliendId << findItems.size();
    if (findItems.isEmpty())
        return;
    const int length = findItems.count();
    for (int i = 0; i < length; ++i){
        auto item = findItems.takeFirst();
        ui->listWidget_trader->removeItemWidget(item);
        delete item;
    }

}

void AdminWindow::slotBtnModifiClicked(const QString &clientId)
{
    QSettings *setting = SettingsLogic::GetInstance()->getSetting();
    setting->beginGroup(clientId);
    QStringList keys = setting->childKeys();
    QVariantMap msgMap;
    foreach(auto key, keys){
        msgMap.insert(key, setting->value(key));
    }

    setting->endGroup();
//    qDebug() << __FUNCTION__ << msgMap << clientId;

    ADialog dialog("修改交易员信息");
    ModifiTraderWidget widget;
    dialog.addWidget(&widget);
    widget.initUiData(msgMap);
    connect(&dialog, &ADialog::signalBtnOkClicked, &widget, &ModifiTraderWidget::slotOkBtnClicked);
    connect(&widget, &ModifiTraderWidget::signalBtnOkClicked, &dialog, &ADialog::accept);

    dialog.exec();
}

void AdminWindow::slotBtnDeleteClicked()
{
    QListWidgetItem *item = ui->listWidget_trader->currentItem();
    QVariantMap dataMap;
    dataMap.insert(DefineFields::funcType, FuncType::DeleteTrader);
    dataMap.insert(DefineFields::UserId, item->text());
    QString errorInfo;
    SettingsLogic::GetInstance()->deleteSetting(dataMap, errorInfo);
    if (!errorInfo.isEmpty())
    {
        QMessageBox::critical(this, "交易员账户删除", errorInfo);
        return;
    }
    ui->listWidget_trader->removeItemWidget(item);
    delete item;
}

void AdminWindow::slotAddTraderClicked()
{
    ADialog dialog("添加交易账号");
    AddTraderWidget widget;
    dialog.addWidget(&widget);
    connect(&dialog, &ADialog::signalBtnOkClicked, &widget, &AddTraderWidget::slotOkBtnClicked);
    connect(&widget, &AddTraderWidget::signalBtnOkClicked, &dialog, &ADialog::accept);
    connect(&widget, &AddTraderWidget::signalBtnOkClicked, this, &AdminWindow::slotAddTraderSuccess);

    dialog.exec();
}

void AdminWindow::slotDeleteTraderClicked()
{
    ADialog dialog("添加交易账号");
    DeleteTraderWidget widget;
    dialog.addWidget(&widget);
    connect(&dialog, &ADialog::signalBtnOkClicked, &widget, &DeleteTraderWidget::slotOkBtnClicked);
    connect(&widget, &DeleteTraderWidget::signalBtnOkClicked, &dialog, &ADialog::accept);
    connect(&widget, &DeleteTraderWidget::signalBtnOkClicked, this, &AdminWindow::slotDeleteTraderSuccess);

    dialog.exec();

}

void AdminWindow::slotAddFundClicked()
{
    ADialog dialog("添加资金账户");
    AddAccountWidget widget;
    dialog.addWidget(&widget);
    connect(&dialog, &ADialog::signalBtnOkClicked, &widget, &AddAccountWidget::slotOkBtnClicked);
    connect(&widget, &AddAccountWidget::signalBtnOkClicked, &dialog, &ADialog::accept);

    dialog.exec();
}

void AdminWindow::slotDeleteFundClicked()
{
    ADialog dialog("删除资金账户");
    DeleteAccountWidget widget;
    dialog.addWidget(&widget);
    connect(&dialog, &ADialog::signalBtnOkClicked, &widget, &DeleteAccountWidget::slotOkBtnClicked);
    connect(&widget, &DeleteAccountWidget::signalBtnOkClicked, &dialog, &ADialog::accept);

    dialog.exec();
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
    ui->stackedWidget->setCurrentWidget(ui->page_user);
    ui->menu_riskManager->clear();
    ui->menu_riskManager->setTitle("");

    QStringList cliendIdList = SettingsLogic::GetInstance()->getSetting()->childGroups();
    foreach(auto cliendId, cliendIdList){
        QListWidgetItem* item = new QListWidgetItem(cliendId);
        AdminUserItem *widget = new AdminUserItem;
        widget->setItemName(cliendId);
        item->setSizeHint(QSize(200, 40));
        ui->listWidget_trader->addItem(item);
        ui->listWidget_trader->setItemWidget(item, widget);
        connect(widget, &AdminUserItem::signalBtnDeleteClicked, this, &AdminWindow::slotBtnDeleteClicked);

        connect(widget, &AdminUserItem::signalBtnModifiClicked, this, &AdminWindow::slotBtnModifiClicked);
    }
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
