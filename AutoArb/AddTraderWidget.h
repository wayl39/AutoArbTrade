#ifndef ADDTRADERWIDGET_H
#define ADDTRADERWIDGET_H

#include <QWidget>

namespace Ui {
class AddTraderWidget;
}

class AddTraderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddTraderWidget(QWidget *parent = nullptr);
    ~AddTraderWidget();

signals:
    void signalBtnOkClicked();

public slots:
    void slotOkBtnClicked();

private slots:
    void slotPVisibleBtnClicked();
private:
    void createWidget();
    void createLayout();
    void createConnect();

    void checkUiData(QString &errorInfo);

    QString checkPassWordValide(const QString& password);
private:
    Ui::AddTraderWidget *ui;
};

#endif // ADDTRADERWIDGET_H
