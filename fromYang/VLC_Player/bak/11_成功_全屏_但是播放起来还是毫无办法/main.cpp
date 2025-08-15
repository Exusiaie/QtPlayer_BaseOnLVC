#include "widget.h"
#include "vlcwidget.h"

#include <QApplication>

/*  // 本版进度
1 - 调整窗口不能打开的 Bug；√​
2 - 调整音量拖动不能被响应的 Bug;  √​
3 - 调整关闭窗口强行停止的 Bug; √​
4 - 检查无边框的功能是否能完成（拉伸，移动等）；√​
5 - 分离底部控制栏 CButtonCtrlBar；​
6 - 实现任务队列界面；​
7 - 实现全屏双击功能；​
8 - 调整 UI，包括进度条；
*/

int main(int argc, char *argv[])
{

/*    // 初始化COM组件
    // - FTH: (12700): *** Fault tolerant heap shim applied to current process. This is usually due to previous crashes. ***
    // - QWindowsContext: OleInitialize() failed:  "COM error 0xffffffff80010106 RPC_E_CHANGED_MODE (Unknown error 0x080010106)"
    // - Qt内部可能也在初始化COM，所以不需要再次初始化，而是交给Qt处理
    // HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);  // 改为 MTA 模式，死机
    if (FAILED(hr))
    {
        // 处理初始化失败的情况
        return -1;
    }

//    ...

//    // 释放COM组件
//    CoUninitialize();
*/

    QApplication a(argc, argv);
    Widget w;
    w.show();
    int result = a.exec();

    return result;
}

