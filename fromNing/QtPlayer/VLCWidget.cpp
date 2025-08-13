#include "vlcwidget.h"
#include "ui_vlcwidget.h"
#include "VLCKits.h"

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

// 两阶段构造 VLCKits对象
VLCWidget::VLCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VLCWidget),
    _pVLCKits(new VLCKits) // 第一阶段: new一个对象
{
    ui->setupUi(this);
    this->setWindowTitle("Ning-Player");

    bool ret = _pVLCKits->initVLC(); // 第二阶段: 调用这个对象的初始化函数
    if(!ret) {
        qDebug("初始化VLCKits对象失败");
        exit(EXIT_FAILURE);
    }

    // 连接VLCKits的信号到VLCWidget的槽
    connect(_pVLCKits.get(), &VLCKits::sigTimeSliderPos, this, &VLCWidget::on_sigTimeSliderPos);
    connect(_pVLCKits.get(), &VLCKits::sigTimeText, this, &VLCWidget::on_sigTimeText);
    connect(_pVLCKits.get(), &VLCKits::sigVolumeSliderPos, this, &VLCWidget::on_sigVolumeSliderPos);

    // 连接UI滑块的信号到VLCWidget的槽
    connect(ui->playSlider, &QSlider::sliderMoved, this, &VLCWidget::on_playSlider_sliderMoved);
    connect(ui->volumeSlider, &QSlider::sliderMoved, this, &VLCWidget::on_volumeSlider_sliderMoved);
}

VLCWidget::~VLCWidget()
{
    delete ui;
}

void VLCWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "@@@@@@@@@@@@@@@@@@@双击事件触发";

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

void VLCWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        this->showNormal();
    }
}

void VLCWidget::on_btnOpen_clicked()
{
    // 使用 QFileDialog::getOpenFileNames 获取多个文件名
      QStringList fileList = QFileDialog::getOpenFileNames(this, "请选择视频文件",
                                                            "C:/Users/18388/Desktop/1. 播放器项目/视频播放器项目资料/videos",
                                                            "视频文件(*.mp4);;视频文件(*.avi);;");
      if (fileList.isEmpty()) {
          return;
      }

      // 调用VLCKits的play方法，传入文件名列表和窗口ID
      // 注意：play函数现在接受的是QStringList，而不是单个QString
      bool ret = _pVLCKits->play(fileList, (void*)ui->videoWidget->winId());
      if(!ret){
          qDebug("文件播放失败");
          return;
      }

      //Windows头文件中的定时器函数
      SetTimer(NULL, 1, 300, TimeProc);
}

void VLCWidget::on_btnPlayer_clicked()
{
    _pVLCKits->play();
}

void VLCWidget::on_btnPause_clicked()
{
    _pVLCKits->pause();
}

void VLCWidget::on_btnStop_clicked()
{
    _pVLCKits->stop();
}

void VLCWidget::on_playSlider_sliderMoved(int position)
{
    // 调用VLCKits的setPosition方法
    _pVLCKits->setPosition(position);
}

void VLCWidget::on_volumeSlider_sliderMoved(int position)
{
    // 调用VLCKits的setVolume方法
    _pVLCKits->setVolume(position);
}

// 新增槽函数，用于响应VLCKits的信号
void VLCWidget::on_sigTimeSliderPos(int value)
{
    ui->playSlider->setValue(value);
}

void VLCWidget::on_sigTimeText(const QString& str)
{
    ui->label->setText(str);
}

void VLCWidget::on_sigVolumeSliderPos(int value)
{
    ui->volumeSlider->setValue(value);
}

// 全屏功能是用户界面逻辑, 放在Widget文件里
void VLCWidget::on_btnFullScreen_clicked()
{
    if (this->isFullScreen()) {
        this->showNormal(); // 如果当前是全屏，则恢复正常模式
    } else {
        this->showFullScreen(); // 如果当前不是全屏，则切换到全屏模式
    }
}






