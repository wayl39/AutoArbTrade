#include <QApplication>
#include "SettingsLogic.h"

#define Test 1

#if Test == 1
#include "AdminWindow.h"
#elif Test == 2
#include "UserWindow.h"
#else
#include "MainWindow.h"
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingsLogic::GetInstance()->init();   
#if Test == 1
    AdminWindow w;
    w.show();
#elif Test == 2
    UserWindow w;
    w.show();
#else
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
