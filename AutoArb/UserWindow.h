#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

    QString clientId() const;
    void setClientId(const QString &clientId);

public slots:
    void slotAddStragetyClicked();

    void slotDeleteStragetyClicked();

    void slotAddRiskClicked();

    void slotDeleteRiskClicked();

private:
    void createWidget();
    void createLayout();
    void createConncet();
private:
    Ui::UserWindow *ui;
    QString m_clientId;
};

#endif // USERWINDOW_H
