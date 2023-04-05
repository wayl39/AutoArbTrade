#ifndef ADDSTRAGETYWIDGET_H
#define ADDSTRAGETYWIDGET_H

#include <QWidget>

namespace Ui {
class AddStragetyWidget;
}

class AddStragetyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddStragetyWidget(QWidget *parent = nullptr);
    ~AddStragetyWidget();

private:
    void createWidget();
    void createLayout();
    void createConnect();


private:
    Ui::AddStragetyWidget *ui;


};

#endif // ADDSTRAGETYWIDGET_H
