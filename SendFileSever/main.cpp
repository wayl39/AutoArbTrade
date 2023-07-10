#include <QApplication>
#include "SettingsLogic.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingsLogic::GetInstance()->init();
//    MainWindow w;
//    w.hide();
    //添加当前目录作为库文件搜索路径
//    QString currentDir = QDir::currentPath();
//    QCoreApplication::addLibraryPath(currentDir);

    return a.exec();
}
