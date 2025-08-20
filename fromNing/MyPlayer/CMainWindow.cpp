#include "CMainWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>

CMainWindow::CMainWindow(QWidget * parent)
    : CFramelessWidget(parent) // 初始化基类CFramelessWidget
{
    initUI(); // 两阶段构造
    //setStyleSheet("background-color: black;"); 这句代码会让CMainWindow的所有子对象都变成黑的
    connect(_ptitleBar, &CTitleBar::sigClose, this, &CMainWindow::closeSlot); // 点击CTitleBar的关闭按钮时，CTitleBar 发出 sigClose 信号，自动调用 CMainWindow 的 closeSlot() 槽函数
    connect(_pmenuWidget, &CMenuWidget::toTestVLCKits, _pVideoWidget, &CVideoWidget::on_btnOpen_clicked);
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_play, _pVideoWidget, &CVideoWidget::on_btnPlayer_clicked);
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_stop, _pVideoWidget, &CVideoWidget::on_btnStop_clicked);
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_fullScreen, _pVideoWidget, &CVideoWidget::on_btnFullScreen_clicked);
    connect(_pVideoWidget, &CVideoWidget::sig_playsstatus, _pbottomCtrBar, &CBottomCtrlBar::setPlaying);

    // 用户拖动底部进度条 -> 告诉 CVideoWidget 去设置播放位置
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_seek,
            _pVideoWidget,   &CVideoWidget::on_playSlider_sliderMoved);

    // 播放进度变化（来自 VLCKits）-> 更新底部进度条显示
    // 方式 A：如果你能拿到 VLCKits 的信号（推荐在 CVideoWidget 暴露访问器）
    connect(_pVideoWidget->getVLCKits(), &VLCKits::sigTimeSliderPos,   // 0~100
            _pbottomCtrBar,           &CBottomCtrlBar::setPositionByPercent);

    connect(_pbottomCtrBar, &CBottomCtrlBar::sliderValueChanged, _pVideoWidget, &CVideoWidget::on_volumeSlider_sliderMoved);
    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_open, _pVideoWidget, &CVideoWidget::on_btnOpen_clicked);
    connect(_pVideoWidget, &CVideoWidget::sigTimeChanged, _pbottomCtrBar, &CBottomCtrlBar::onTimeChanged);
    //   connect(_pplayButtonGroupWidget, &CPlayButtonGroupWidget::sig_pre, _pVideoWidget, &CVideoWidget::on_btnPlayer_clicked);
 //   connect(_pplayButtonGroupWidget, &CPlayButtonGroupWidget::sig_next, _pVideoWidget, &CVideoWidget::on_btnPlayer_clicked);


//    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_play, this, &CVideoWidget::on_btnOpen_clicked);
//    connect(_pbottomCtrBar, &CBottomCtrlBar::sig_stop, _pVLCKits, &VLCKits::stop);

    // 全屏功能后续再实现
    // connect(_pbottomCtrBar, &CBottomCtrlBar::sig_fullScreen, _pVLCKits, &VLCKits::handleFullScreen);
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
    _pVideoWidget = new CVideoWidget(this);



    // 创建一个垂直布局, 把 CTitleBar,QWidget添加进去, 并把布局的内边距设为0, 确保他两都紧贴窗口边缘
    QVBoxLayout * pvLayout = new QVBoxLayout(this);
    pvLayout->addWidget(_ptitleBar);
    pvLayout->addWidget(_pmenuWidget);
    pvLayout->addWidget(_pVideoWidget, 1); // 第二个参数 1 表示拉伸因子，让它占据更多空间
    pvLayout->addWidget(_pbottomCtrBar);

    pvLayout->setContentsMargins(0, 0, 0, 0);
    pvLayout->setSpacing(0);
    setLayout(pvLayout);


    // 让标题栏、菜单和底部控制栏不被拉伸，视频区域填充
//        pvLayout->setStretchFactor(_ptitleBar, 0);
//        pvLayout->setStretchFactor(_pmenuWidget, 0);
//        pvLayout->setStretchFactor(_pVideoWidget, 1);
//        pvLayout->setStretchFactor(_pbottomCtrBar, 0);
    adjustSize();
    resize(1000, 700);
}

