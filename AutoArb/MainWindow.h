#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"

class AdminWindow;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotLogSuccess(const QString& cliendId);

private:
    void createWidget();
    void createLayout();
    void createConnect();

private:
    Ui::MainWindow *ui;
    LoginWidget* m_logWidget{Q_NULLPTR};
    AdminWindow *m_adminWindow{Q_NULLPTR};
};

#endif // MAINWINDOW_H
