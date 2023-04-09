#include "MainWindow.h"
#include <QApplication>
#include "SettingsLogic.h"

#define Test 1

#ifdef Test
#include "AdminWindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingsLogic::GetInstance()->init();   
#if Test
    AdminWindow w;
    w.show();
#else
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
