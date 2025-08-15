#include "widget.h"
#include "vlcwidget.h"

#include <QApplication>

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

