#include <QApplication>
#include "SettingsLogic.h"
#include <QThread>

#define Test 0

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
    QThread* t = new QThread;
    SettingsLogic::GetInstance()->moveToThread(t);
    t->start();
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
    qDebug() << __FUNCTION__ << "主线程Id：" << QThread::currentThread();
    return a.exec();
}
