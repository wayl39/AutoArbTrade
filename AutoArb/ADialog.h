#ifndef ADIALOG_H
#define ADIALOG_H

#include <QDialog>

namespace Ui {
class ADialog;
}

class ADialog : public QDialog
{
    Q_OBJECT

public:
    explicit ADialog(const QString& title = "", QWidget *parent = nullptr);
    ~ADialog();

    void addWidget(QWidget* widget);

private:
    Ui::ADialog *ui;
};

#endif // ADIALOG_H
