#include "CMainWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>

CMainWindow::CMainWindow(QWidget * parent)
    : CFramelessWidget(parent) // 初始化基类CFramelessWidget
{
    initUI(); // 两阶段构造
    connect(_ptitleBar, &CTitleBar::sigClose, this, &CMainWindow::closeSlot); // 点击CTitleBar的关闭按钮时，CTitleBar 发出 sigClose 信号，自动调用 CMainWindow 的 closeSlot() 槽函数
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_play, _ptestVLCKits, &TestVLCKits::handlePlay);
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_stop, _ptestVLCKits, &TestVLCKits::handleStop);
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_fullScreen, _ptestVLCKits, &TestVLCKits::handleFullScreen);


}

// CMainWindow 的 closeSlot() 槽函数
void CMainWindow::closeSlot()
{
    QMessageBox::StandardButton isExit = QMessageBox::warning(this, "提示", "确定要退出吗？",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes); // 标准警告框
    if(isExit == QMessageBox::Yes) { // 在警告框中点了Yes就执行 close (QWidget的公有方法)
        close();
    }
}


void CMainWindow::initUI()
{
    _ptitleBar = new CTitleBar(this);   // 创建一个 CTitleBar 对象，并将其父对象设为 this (即 CMainWindow 实例)
    _pbottomCtrBar = new CBottomCtrlBar(this);
    _pmenuWidget = new CMenuWidget(this);

   _ptestVLCKits = new TestVLCKits(this);


    QWidget * wbody = new QWidget(this);    // 创建一个 QWidget 对象，作为窗口的主体部分
    wbody->setMinimumSize(800, 600);    // 设置窗口最小大小

    // 创建一个垂直布局, 把 CTitleBar,QWidget添加进去, 并把布局的内边距设为0, 确保他两都紧贴窗口边缘
    QVBoxLayout * pvLayout = new QVBoxLayout(this);
    pvLayout->addWidget(_ptitleBar);
    pvLayout->addWidget(_pmenuWidget);

    pvLayout->addWidget(_pbottomCtrBar);

    pvLayout->addWidget(wbody);
    pvLayout->setContentsMargins(0, 0, 0, 0);
}

