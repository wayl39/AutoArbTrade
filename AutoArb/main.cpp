#include "MainWindow.h"
#include <QApplication>
#include "AdminWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    AdminWindow w;
    w.show();

    return a.exec();
}
