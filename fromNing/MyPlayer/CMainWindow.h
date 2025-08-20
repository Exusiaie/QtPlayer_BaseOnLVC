#ifndef CMAINWINDOWS_H
#define CMAINWINDOWS_H

#include "CFramelessWidget.h"
#include "CTitleBar.h"
#include "CBottomCtrlBar.h"
#include "CMenuWidget.h"
#include "CVideoWidget.h"

#include <QWidget>

class CMainWindow : public CFramelessWidget //建议使用继承，而不是组合
{
    Q_OBJECT
public: // 对象树, 当一个控件的构造函数中传入一个父控件指针时，这个控件就会成为父控件的子控件
    explicit CMainWindow(QWidget * parent= nullptr);   // nullptr:  没有父对象, 就是顶级窗口

signals:
    void open();

private slots:
    void closeSlot();

private:
    void initUI();

private:
    CTitleBar               * _ptitleBar;
    CBottomCtrlBar          * _pbottomCtrBar;
    CMenuWidget             * _pmenuWidget;

    CVideoWidget            * _pVideoWidget;
};

#endif // CMAINWINDOWS_H
