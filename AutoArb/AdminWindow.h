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

public slots:
    void slotAddTraderSuccess(const QString& cliendId);

    void slotDeleteTraderSuccess(const QString& cliendId);

    void slotBtnModifiClicked(const QString& clientId);

    void slotBtnDeleteClicked(const QString &cliendId);

    void slotSettingFile(const QVariantMap& dataMap);
    void slotReadTraderMsg(const QVariantMap& dataMap);

    void slotDeleteTraderMsg(const QVariantMap& dataMap);
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
