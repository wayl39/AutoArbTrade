#include "MainWindow.h"
#include <QApplication>
#include "AdminWindow.h"
#include "SettingsLogic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    SettingsLogic::GetInstance()->init();
    AdminWindow w;
    w.show();

    return a.exec();
}
