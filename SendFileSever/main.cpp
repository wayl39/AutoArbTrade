#include "MainWindow.h"
#include <QApplication>
#include "SettingsLogic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingsLogic::GetInstance()->init();
//    MainWindow w;
//    w.hide();

    return a.exec();
}
