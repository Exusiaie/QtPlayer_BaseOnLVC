#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "cframelesswidget.h"
#include "ctitlebar.h"

class CMainWindow
        : public CFramelessWidget
{
    Q_OBJECT
public:
    explicit CMainWindow(QWidget * parent= nullptr);

private slots:
    void closeSlot();//与子对象CTitleBar::sigClose信号绑定

private:
    void initUI();

private:
    CTitleBar * _ptitleBar;//主窗口中包含标题栏
};
#endif // CMAINWINDOW_H
