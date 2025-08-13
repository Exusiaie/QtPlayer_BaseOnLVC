#include "CFramelessWidget.h"
#include "CMainWindow.h"

#include <QApplication>

// 只有一个无边框窗口
//int test0(QApplication & a)
//{
//    CFramelessWidget w;
//    w.show();
//    return a.exec();
//}
// 只有一个菜单栏
//int test2(QApplication & a)
//{
//    CTitleBar w;
//    w.show();
//    return a.exec();
//}

// 主窗口
int mainWindow(QApplication & a)
{
    CMainWindow w;
    w.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow(a);
    return a.exec();
}

