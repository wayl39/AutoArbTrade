#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHBoxLayout>
#include "DefineFields.h"
#include "SettingsLogic.h"
#include "AdminWindow.h"
//#include "

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createWidget();
    createLayout();
    createConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLogSuccess(const QString &cliendId)
{
    if (cliendId == SettingsLogic::GetInstance()->getSettingValue(DefineFields::Admin_Account).toString()){
        close();
        m_adminWindow = new AdminWindow;
        m_adminWindow->show();
    } else {
        close();

    }
}

void MainWindow::createWidget()
{
    m_logWidget = new LoginWidget(this);
}

void MainWindow::createLayout()
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_logWidget);
    ui->centralWidget->setLayout(layout);
}

void MainWindow::createConnect()
{
    connect(m_logWidget, &LoginWidget::signalLogSuccess, this, &MainWindow::slotLogSuccess);
}
