#ifndef ADMINUSERITEM_H
#define ADMINUSERITEM_H

#include <QWidget>

namespace Ui {
class AdminUserItem;
}

class AdminUserItem : public QWidget
{
    Q_OBJECT

public:
    explicit AdminUserItem(QWidget *parent = nullptr);
    ~AdminUserItem();

    void setItemName(const QString& text);

signals:
    void signalBtnDeleteClicked(const QString& cliendId);

    void signalBtnModifiClicked(const QString& cliendId);

private:
    void createWidget();
    void createLayout();
    void createConnect();

private:
    Ui::AdminUserItem *ui;

    QString m_clientId;
};

#endif // ADMINUSERITEM_H
