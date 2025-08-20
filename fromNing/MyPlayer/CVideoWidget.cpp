#include "CVideoWidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>  // 创建文件对话框的库
#include <QMessageBox>  // 创建标准消息框(错误, 警告, 询问, 信息)
#include <QMouseEvent>
#include <windows.h>

BOOL CALLBACK EnumVLC(HWND hwnd, LPARAM lParam)
{
    TCHAR szTitle[1024];

    int nLen = GetWindowText(hwnd, szTitle, 1024);

    if (nLen > 0)
    {
//        qDebug() << "禁用此窗口";
        EnableWindow(hwnd, FALSE);
        KillTimer(NULL, 1);
    }

    return TRUE;
}

void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
{
    HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"Ning-Player");

    if (vlcHwnd)
    {
        EnumChildWindows(vlcHwnd, EnumVLC, NULL);
    }
}

CVideoWidget::CVideoWidget(QWidget *parent) : QWidget(parent)
{

    setAttribute(Qt::WA_StyledBackground);
    setWindowFlags(Qt::FramelessWindowHint);

      this->setStyleSheet("background-color: black;"); // 设置背景为黑色，方便看到区域
      this->setMinimumSize(800, 450); // 设置一个最小尺寸

    // 初始化 VLCKits
    _pVLCKits = new VLCKits(this);
    if (!_pVLCKits->initVLC()) {
        qDebug() << "VLC内核初始化失败！";
        exit(1);
    }
    connect(_pVLCKits, &VLCKits::sigTimeChanged, this, &CVideoWidget::sigTimeChanged);
    qDebug() << "创建完成";
   // QMessageBox::information(this, 11, 22);


}


CVideoWidget::~CVideoWidget()
{
    // 确保在 CVideoWidget 销毁时 VLCKits 也被销毁
    if (_pVLCKits) {
        _pVLCKits->stop();
        delete _pVLCKits;
        _pVLCKits = nullptr;
    }
}

void CVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 检查双击事件是否由鼠标左键触发
     if (event->button() == Qt::LeftButton) {
         // 获取当前播放器状态
         libvlc_state_t state = libvlc_media_player_get_state(_pVLCKits->mediaPlayer());

         // 如果正在播放或已暂停，则进行暂停/播放切换
         if (state == libvlc_Playing) {
           _pVLCKits->pause();
         }else if(state == libvlc_Paused){
             _pVLCKits->play();
         }

         // 接受事件，防止传递给父窗口
         event->accept();
     }
}

void CVideoWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        this->showNormal();
    }
}

void CVideoWidget::on_btnOpen_clicked()
{
    // 逻辑和 VLCWidget::on_btnOpen_clicked() 完全一样
    QStringList fileList = QFileDialog::getOpenFileNames(this, "请选择视频文件",
                                                          "C:/Users/18388/Desktop/1. 播放器项目/视频播放器项目资料/videos", // 可以设置一个默认路径
                                                          "视频文件(*.mp4 *.avi *.mkv);;所有文件(*.*)");
    if (fileList.isEmpty()) {
        return;
    }

    // 调用VLCKits的play方法，传入文件名列表和 videoWidget 的窗口句柄
    // winId() 函数返回窗口系统的特定标识符，VLC需要用它来确定在哪里渲染视频
    bool ret = _pVLCKits->play(fileList, (void*)this->winId());
    if(!ret){
        QMessageBox::critical(this, "错误", "文件播放失败");
        return;
    }
    emit sig_playsstatus(true);

     SetTimer(NULL, 1, 300, TimeProc);
}

void CVideoWidget::on_btnPlayer_clicked()
{

    libvlc_state_t state = libvlc_media_player_get_state(_pVLCKits->mediaPlayer());

    // 如果正在播放或已暂停，则进行暂停/播放切换
    if (state == libvlc_Playing) {
      _pVLCKits->pause();
      emit sig_playsstatus(false);
    }else if(state == libvlc_Paused){
        _pVLCKits->play();
        emit sig_playsstatus(true);
    }
}

void CVideoWidget::on_btnPause_clicked()
{
    _pVLCKits->pause();
}

void CVideoWidget::on_btnStop_clicked()
{
    _pVLCKits->stop();
}

void CVideoWidget::on_playSlider_sliderMoved(int position)
{
    _pVLCKits->setPosition(position);
}

void CVideoWidget::on_volumeSlider_sliderMoved(int position)
{
    _pVLCKits->setVolume(position);
}

void CVideoWidget::on_btnFullScreen_clicked()
{
    QWidget *top = window(); // 获取顶层窗口（CMainWindow）
    if (top->isFullScreen()) {
        top->showNormal();
    } else {
        top->showFullScreen(); // 让顶层窗口全屏
    }
}

