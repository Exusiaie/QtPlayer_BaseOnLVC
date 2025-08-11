#include "vlcwidget.h"
#include "ui_vlcwidget.h"

#include <QDebug>
#include <QFileDialog>  // 创建文件对话框的库
#include <QMessageBox>  // 创建标准消息框(错误, 警告, 询问, 信息)

VLCWidget::VLCWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VLCWidget)
    , _pinstance(nullptr)       // 构造函数构造了一个VLC实例, 构造的顺序一般遵循:
    ,_pmedia_player(nullptr)    // VLC 实例 (_pinstance) -> 媒体播放器 (_pmediaPlayer) -> 媒体 (_pmedia)
    ,_pmedia(nullptr)
{
    ui->setupUi(this);
    qDebug() << "VLCWidget() 完成";
}

VLCWidget::~VLCWidget()
{
    delete ui;
    libvlc_media_release(_pmedia);              // libvlc_..._release() 系列函数:
    libvlc_media_player_release(_pmedia_player);// 这是 VLC API 的核心部分。它负责释放之前分配的 VLC 资源。
    libvlc_release(_pinstance);                 // 释放顺序通常是反向的：先释放媒体 (_pmedia)，再释放媒体播放器 (_pmediaPlayer)，最后释放 VLC 实例 (_pinstance)
    qDebug() << "~VLCWidget() 完成";
}

// 接下来实现那四个按钮对应的槽函数
// 第一个按钮: 打开文件
void VLCWidget::on_btnOpen_clicked(){
    qDebug() << "btnOpen按钮被按下";
    // 打开文件对话框: QFileDialog::getOpenFileName(...) 弹出一个文件选择对话框，返回用户选择的QString类型文件路径(若用户取消选择将返回一个空字符串), 正因如此可以用判空操作来判断用户是否选择了文件
    QString filename = QFileDialog::getOpenFileName(this, "请选择视频文件", "D:/", "视频文件(*.mp4);;" "视频文件(*.avi);;");
    if(filename.isEmpty()){
        qDebug("用户取消操作");
        return;
    }
    // 路径转换, 这一步非常重要，它将 Qt 的 / 风格路径转换为操作系统原生的 \ 风格路径 (Windows 上)，以确保 VLC 库能正确识别路径。
    filename = QDir::toNativeSeparators(filename);
    qDebug("成功获取文件路径");
    // 先配置参数, 再使用libvlc_new初始化一个VLC实例
    const char* vlc_args[] = {
        //"--no-plugins-cache",     // 禁用插件缓存（若问题仍存在则关闭）
        "--ignore-config",          // 忽略全局配置文件
        "--quiet",                  // 静默模式（减少日志）
        "--no-video-title-show",    // 禁用标题显示
        //"--avcodec-hw=any"        // 启用硬件加速（可选）
    };
    // 1. 初始化一个vlc实例, (vlc_args参数的个数, 配置好的vlc_args)
    _pinstance = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]), vlc_args);
    if(_pinstance == nullptr){
        QMessageBox::information(this, "提示", "libvlc_new Failed");
        exit(EXIT_FAILURE);
    }
    // 2. 创建媒体对象, 使用vlc实例和获得的文件路径创建一个媒体对象, 此时媒体还未被加载
    _pmedia = libvlc_media_new_path(_pinstance, filename.toStdString().c_str());
    // 3. 创建媒体播放器, 使用媒体对象创建一个媒体播放器, 用于控制这个媒体
    _pmedia_player = libvlc_media_player_new_from_media(_pmedia);
    if(_pmedia_player == nullptr) {
        libvlc_release(_pinstance);
        QMessageBox::information(this, "提示", "libvlc_media_player_new_from_media failed!");
        exit(EXIT_FAILURE);
    }
    // 4. 将播放器的输出窗口句柄设置为 ui界面中的widgetVideo 的窗口 ID (winId())，这样视频就会在 Qt 的 videoWidget 上显示。
    // winId() 窗口原生句柄
    libvlc_media_player_set_hwnd(_pmedia_player, (void*)ui->widgetVideo->winId());
    QMessageBox::information(this, "已加载好文件", "请点击播放按钮");
}

void VLCWidget::on_btnPlayer_clicked(){
    qDebug() << "btnPlayer按钮被按下";
    // 5. 开始播放
    // 用来获取播放器状态的函数, 该函数返回⼀个 libvlc_state_t 类型的枚举值，⽤以表⽰媒体播放器当前的状
    libvlc_state_t state = libvlc_media_player_get_state(_pmedia_player);
    qDebug() << "state: " << state;
    // if判断如果播放器处于 暂停 (libvlc_Paused)、停止 (libvlc_Stopped) 或 没有特别事情 (libvlc_NothingSpecial) 的状态时，才执行播放操作
    if(state == libvlc_Paused || state == libvlc_Stopped || state == libvlc_NothingSpecial){
        libvlc_media_player_play(_pmedia_player);
    }
}

void VLCWidget::on_btnPause_clicked(){
    qDebug() << "btnPause按钮被按下";
    // 6. 暂停播放
    // 获取播放器的状态, 只有当播放器处于播放状态才会执行暂停操作
    libvlc_state_t state = libvlc_media_player_get_state(_pmedia_player);
    qDebug() << "state: " << state;
    if(state == libvlc_Playing){
        libvlc_media_player_pause(_pmedia_player);
    }
}

void VLCWidget::on_btnStop_clicked(){
    qDebug() << "btnStop按钮被按下";
    // 7. 停止播放
    // 获取播放器状态, 只有当播放器正在播放或正在暂停才会执行停止播放操作
    libvlc_state_t state = libvlc_media_player_get_state(_pmedia_player);
    qDebug() << "state: " << state;
    if(state == libvlc_Playing || state == libvlc_Paused){
        libvlc_media_player_stop(_pmedia_player);
    }
}
