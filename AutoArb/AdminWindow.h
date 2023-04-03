#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void slotAddTraderClicked();
    void slotDeleteTraderClicked();
    void slotAddFundClicked();
    void slotDeleteFundClicked();
    void slotAddRiskClicked();
    void slotDeleteRiskClicked();

private:
    void createWidget();
    void createLayout();
    void createConnect();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H