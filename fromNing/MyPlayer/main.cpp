#include "CFramelessWidget.h"
#include "CMainWindow.h"

#include "CBottomCtrlBar.h"

#include <QApplication>

int test0(QApplication & a)
{
    CBottomCtrlBar w;
    w.show();
    return a.exec();
}


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

