#include "vlcwidget.h"

#include <qevent.h>     // 增加鼠标与键盘事件
#include <windows.h>    // 处理vlc双击全屏与退出全屏的事件
#include <objbase.h>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSlider>
#include <QFileDialog>
#include <QMessageBox>

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);

VLCWidget::VLCWidget(QWidget *parent)
    : QWidget(parent)
    , m_vlc_instance(nullptr)
    , m_media(nullptr)
    , m_media_player(nullptr)
    , m_event_manager(nullptr)
    , m_duration_seconds(0)
    , m_video_widget(nullptr)
    , m_fullscreen_timer(nullptr)
    , m_time_slider(nullptr)
    , m_time_label(nullptr)
    , m_volume_slider(nullptr)
    , m_volume_label(nullptr)
{
/*     Windows平台兼容问题，初始化COM组件
     - 此处初始化引起报错：mmdevice audio output error: cannot initialize COM (error 0x80010106)
     - 错误代码 0x80010106 表示COM组件已经被初始化，但使用了不同的线程模型
     - 目前交给Main初始化
    CoInitialize(NULL);
*/
    log_info("");
}

HWND VLCWidget::original_vlc_parent = NULL; // 初始化

VLCWidget::~VLCWidget()
{
    //CoUninitialize();       // 析构COM组件(目前交给main函数初始化，否则会报错）
    unbind_events(); // 加这一行
    if (m_media_player)
    {
        libvlc_media_player_stop(m_media_player);
        libvlc_media_player_release(m_media_player);
        m_media_player = nullptr;
    }
    if (m_media)
    {
        libvlc_media_release(m_media);
        m_media = nullptr;
    }
    if (m_vlc_instance)
    {
        libvlc_release(m_vlc_instance);
        m_vlc_instance = nullptr;   
    }
    log_info("");
}

// 设置部件：播放窗口
void VLCWidget::set_video_widget(QWidget *widget)
{
    m_video_widget = widget;

    if(m_video_widget)
    {
        // 添加必要的窗口属性设置，帮助VLC正确识别窗口
        m_video_widget->setAttribute(Qt::WA_OpaquePaintEvent);
        m_video_widget->setAttribute(Qt::WA_NoSystemBackground);
        m_video_widget->setAttribute(Qt::WA_PaintOnScreen);     // 允许直接在屏幕上绘制
        m_video_widget->setFocusPolicy(Qt::StrongFocus);        // 确保窗口能接收键盘事件

        // 强制启用窗口，确保能接收鼠标输入
        HWND hwnd = (HWND) m_video_widget->winId();
        EnableWindow(hwnd, TRUE);

        // 只有在媒体播放器初始化后才设置窗口句柄,否则会报错
        if(m_media_player)
        {
            // 确保在主线程中设置窗口句柄
            QMetaObject::invokeMethod(this, [this](){
                libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
            }, Qt::QueuedConnection);
        }

        // 使用Qstring进行字符拼接
        QString logMessage = QString("Video widget set with handle: %1").arg(m_video_widget->winId());
        log_info(logMessage.toUtf8().constData());
    }

    if (m_video_widget && m_media_player) {
        libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
        HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
        if (vlcHwnd && original_vlc_parent == NULL) {
            original_vlc_parent = GetParent(vlcHwnd); // 记录原始父窗口
        }
    }
}

// 双击全屏
void VLCWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

/*  // 强制将窗口置为前台，此处在系统默认时有设置
    if(m_video_widget)
    {
        m_video_widget->raise();
        m_video_widget->activateWindow();
    }
*/
/*  // vlc全屏切换与Qt窗口管理存在冲突，代码失效
    log_info("Mouse double click event received");

    // 全屏功能交给vlc实现
    if (!m_media_player || !m_video_widget)
    {
        event->accept();
        return;
    }

    // 当前全屏状态
    bool is_fullscreen = libvlc_get_fullscreen(m_media_player);
    // 普通流程：尝试强制全屏
    libvlc_set_fullscreen(m_media_player, !is_fullscreen);  // 此处不能返回bool，会报错 -> vlcwidget.cpp:124:10: error: cannot initialize a variable of type 'bool' with an rvalue of type 'void'

    // 验证是否成功设置
    bool success = libvlc_get_fullscreen(m_media_player);
    log_info(QString("Toggle fullscreen: %1, Success: %2")
             .arg(!is_fullscreen).arg(success).toUtf8().constData());

    // 如果VLC全屏失败，尝试使用Qt全屏
    if(!success)
    {
        log_info("VLC fullscreen failed, trying Qt fullscreen");
        if(!is_fullscreen)
        {
            // 进入全屏
            this->showFullScreen();
        }
        else
        {
            // 退出全屏
            this->showNormal();
        }
    }
    event->accept();
    QWidget::mouseDoubleClickEvent(event);
*/

    // 舍弃vlc全屏切换与Qt，改为由windows API接管
    log_info("Mouse double click event received");

    // 全屏功能交给vlc实现
    if (!m_media_player || !m_video_widget)
    {
        event->accept();
        return;
    }

    // 获取当前窗口状态
    // - 确保进入 / 退出全屏时完全掌控 VLC 窗口的父窗口和样式，阻止事件传递给 VLC 内部
    HWND mainHwnd = (HWND)this->winId();
    HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
    WINDOWPLACEMENT wp;
    wp.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(mainHwnd, &wp);

    bool is_fullscreen = (wp.showCmd == SW_SHOWMAXIMIZED);

    if (!is_fullscreen) {
        // 进入全屏：强制VLC窗口作为子窗口填充播放区域
        SetWindowPlacement(mainHwnd, &wp);
        ShowWindow(mainHwnd, SW_SHOWMAXIMIZED);

        if (vlcHwnd && IsWindow(vlcHwnd)) {
            // 记录VLC窗口原始父窗口（用于退出时恢复）
            original_vlc_parent = GetParent(vlcHwnd);
            // 设置为m_video_widget的子窗口，样式为填充父窗口
            SetParent(vlcHwnd, (HWND)m_video_widget->winId());
            SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
            // 强制VLC窗口大小与m_video_widget一致
            RECT rect;
            GetClientRect((HWND)m_video_widget->winId(), &rect);
            SetWindowPos(vlcHwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
            ShowWindow(vlcHwnd, SW_SHOW);
        }
        log_info("Entered fullscreen mode (custom)");
    } else {
        // 退出全屏：恢复VLC窗口原始父窗口和样式
        ShowWindow(mainHwnd, SW_SHOWNORMAL);

        if (vlcHwnd && IsWindow(vlcHwnd)) {
            // 恢复原始父窗口（通常是桌面窗口）
            SetParent(vlcHwnd, original_vlc_parent);
            // 恢复窗口样式为顶层窗口
            SetWindowLong(vlcHwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
            // 重新绑定到m_video_widget（确保正常显示）
            RECT rect;
            GetClientRect((HWND)m_video_widget->winId(), &rect);
            SetWindowPos(vlcHwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
            ShowWindow(vlcHwnd, SW_SHOW);
        }
        log_info("Exited fullscreen mode (custom)");
    }

    event->accept();
    //QWidget::mouseDoubleClickEvent(event); //不要调用, 避免触发VLC的默认处理
}

// 键盘全屏
void VLCWidget::keyPressEvent(QKeyEvent *event)
{
/*  // 退出全屏功能交给Qt实现，失败
    if(event->key() == Qt::Key_Escape && this->isFullScreen())
    {
        this->showNormal();
        event->accept();    // 接收事件
    }
    else
    {
        event->ignore();    // 忽略事件，让父类处理
        QWidget::keyPressEvent(event);      // 调用父类实现
    }
*/
/*  // 退出全屏功能交给vlc实现，失败
    if(event->key() == Qt::Key_Escape)
    {
        if(m_media_player)
        {
            bool is_fullscreen = libvlc_get_fullscreen(m_media_player);
            if(is_fullscreen)
            {
                libvlc_set_fullscreen(m_media_player, false);
                event->accept();    // 接收事件；不需要调用父类实现，因为我们已经完全处理了该事件
                return;
            }

        }
    }
*/
    // 退出全屏功能交给windows API实现
    if (event->key() == Qt::Key_Escape) {
        HWND mainHwnd = (HWND)this->winId();
        WINDOWPLACEMENT wp;
        wp.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(mainHwnd, &wp);

        if (wp.showCmd == SW_SHOWMAXIMIZED) {
            // 退出全屏，逻辑与双击退出完全一致
            ShowWindow(mainHwnd, SW_SHOWNORMAL);
            HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
            if (vlcHwnd && IsWindow(vlcHwnd)) {
                SetParent(vlcHwnd, original_vlc_parent); // 使用上面记录的原始父窗口
                SetWindowLong(vlcHwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                RECT rect;
                GetClientRect((HWND)m_video_widget->winId(), &rect);
                SetWindowPos(vlcHwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
                ShowWindow(vlcHwnd, SW_SHOW);
            }
            log_info("Exited fullscreen via Escape (custom)");
            event->accept();
            return;
        }
    }

    // 其它按键时间交给父类处理
    QWidget::keyPressEvent(event);
}

void VLCWidget::check_fullscreen_state()
{
    if(m_media_player)
    {
        static bool last_state = false;
        bool current_state = libvlc_get_fullscreen(m_media_player);
        if(current_state != last_state)
        {
            log_info(QString("Fullscreen state changed: %1 -> %2").arg(last_state ? "true" : "false").arg(current_state ? "true" : "false").toUtf8().constData());
            last_state = current_state;

            // 确保窗口状态与VLC状态匹配
            if(m_video_widget)
            {
                if(current_state && !m_video_widget->isFullScreen())
                {
                    m_video_widget->showFullScreen();
                }
                else if(!current_state && m_video_widget->isFullScreen())
                {
                    m_video_widget->showNormal();
                }
            }
        }
    }
}

/*
//// 设置部件：时间进度条
//void VLCWidget::set_timer_slider_value(int value)
//{
//    if(m_time_slider)
//    {
//        m_time_slider->setValue(value);
//    }
//}

//// 设置部件：时间显示
//void VLCWidget::set_timer_text(const QString& text)
//{
//    if(m_time_label)
//    {
//        m_time_label->setText(text);
//    }
//}

//// 设置部件：音量滑块值
//void VLCWidget::set_volume_slider_value(int value)
//{
//    if(m_volume_slider)
//    {
//        m_volume_slider->setValue(value);
//    }
//}
*/

// 设置部件：进度条与音量
void VLCWidget::vlc_callback(const struct libvlc_event_t *p_event, void *p_data)
{
    log_info("");
    VLCWidget * p = static_cast<VLCWidget*>(p_data);
    if(p)
    {
        switch (p_event->type)
        {
            case libvlc_MediaPlayerPositionChanged:
            {
                // 获取到的是一个百分比
                float pos = libvlc_media_player_get_position(p->get_media_player());
//                p->set_timer_slider_value(static_cast<int>(pos * 100));
                emit p->set_timer_slider_value(static_cast<int>(pos * 100));    // 发送信号
                // 设置视频的时间
                qint64 totalSec = p->get_duration_time();
                qDebug() << "duration time:" << totalSec;
                // 实现效果：
                int HH = totalSec / 3600;
                int MM = (totalSec - HH * 3600) / 60;
                int SS = totalSec - HH *3600 - MM * 60;
                qint64 curSec = libvlc_media_player_get_time(p->get_media_player()) / 1000;
                int curHour = curSec / 3600;
                int curMinute = (curSec - curHour * 3600) / 60;
                int curSecs = curSec - curHour * 3600 - curMinute * 60;
                char buff[64] = {0};
                sprintf(buff, "%02d:%02d:%02d/%02d:%02d:%02d",
                        curHour, curMinute, curSecs,
                        HH, MM, SS);
                QString str(buff);
                emit p->set_timer_text(str);
                break;
            }
            case libvlc_MediaPlayerAudioVolume:
            {
                int val = libvlc_audio_get_volume(p->get_media_player());
                emit p->set_volume_slider_value(val);
                break;
            }
        }
    }
}

//// 窗口枚举回调函数
//// - 遍历窗口，获取窗口标题，如果标题不为空，则禁用该窗口并停止计时器
//// - 可能用于禁用vlc播放器相关窗口的交互
//BOOL CALLBACK VLCWidget::EnumVLC(HWND hwnd, LPARAM lParam)
//{
//    TCHAR szTitle[1024];
//    int nLen = GetWindowText(hwnd, szTitle, 1024);
//    if (nLen > 0)
//    {
//        EnableWindow(hwnd, FALSE);
//        KillTimer(NULL, 1);
//    }
//    return TRUE;
//}

//// 回调函数
//// - 定时查找标题为“王道播放器的窗口”，如果找到，则枚举其子窗口并对每个子窗口调用EnumVLC函数
//// - 可能用于解决VLC播放窗口与Qt窗口之间的交互问题
//void CALLBACK VLCWidget::TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
//{
//    HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"王道播放器");
//    if (vlcHwnd)
//    {
//        EnumChildWindows(vlcHwnd, EnumVLC, NULL);
//    }
//}

void VLCWidget::on_openbtn_clicked()
{
//    // 0. 初始化COM组件
//    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
//    if (FAILED(hr) && hr != S_FALSE)
//    {
//        QMessageBox::critical(this, "错误", "COM组件初始化失败!");
//        return;
//    }

    // 1. 打开文件
    log_info("");
//    CoInitialize(NULL);         // Windows平台兼容问题，初始化COM组件
    QString filename = QFileDialog::getOpenFileName    // Qt标准GUI组件
    (
        this,                   // 指向父窗口的指针
        "请选择视频文件",         // 文件对话框的标题
        "D:/",                  // 对话框打开时的初始目录
        "视频文件(*.mp4);;"      // 文件过滤器，限定用户只能选择mp4或avi格式的视频
        "视频文件(*.avi);;"
    );

    qDebug() << "filename:" << filename;
    // 注意:这一步必须要做,否则就会有bug
    filename = QDir::toNativeSeparators(filename);

    if(filename.isEmpty()) {
        return;
    }

    // 释放之前的VLC实例
    // - 解决频繁切换打开文件的问题
    if(m_media_player)
    {
        libvlc_media_player_stop(m_media_player);
        libvlc_media_player_release(m_media_player);
        m_media_player = nullptr;
    }

    if(m_vlc_instance)
    {
        libvlc_release(m_vlc_instance);
        m_vlc_instance = nullptr;
    }

    // 2. 创建vlc实例
    const char* vlc_args[] =
    {

        "--ignore-config",      // 忽略全局配置文件
        "--quiet",              // 静默模式（减少日志）
        "--directx-use-sysmem", // 使用系统内存而非显存（解决windows平台下某些显卡兼容性问题）
        "--no-video-title-show",// 禁用标题显示
        "--no-snapshot-preview",// 禁用快照预览
        "--no-osd",
        "--no-fullscreen",      // 禁用VLC全屏
        "--no-video-deco",      // 禁用视频窗口装饰（避免VLC窗口自带边框干扰）
        "--no-embedded-video",  // 禁用嵌入式视频处理（防止VLC接管窗口布局）
        "--aout=directsound",   // 强制使用 directsound 音频输出，解决报错：mmdevice audio output error: cannot initialize COM错误
    };
        //"--directx-device=desktop", // 使用桌面设备
        //"--no-plugins-cache", // 禁用插件缓存（若问题仍存在则关闭）
        //"--qt-fullscreen-screennumber=0",  // 指定全屏显示器
        //"--video-on-top",       // 视频窗口置顶
        //"--no-disable-screensaver", // 禁用屏幕保护程序
        //
        //"--no-qt-video-autoresize",  // 禁用视频自动调整大小（不知道是不是与当前qt设置冲突，因此不选）
        //"--avcodec-threads=2",  // 限制解码线程数（在windows平台下减少资源竞争，实测添加后容易死锁）
        //"--video-x11-display=:0", // 设置X11显示（Windows平台兼容，该版本不支持）
        //"--directx-force-yuv",  // 强制YUV渲染（该版本不支持）
        //"--avcodec-hw=any"    // 启用硬件加速（可选）

    m_vlc_instance = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]), vlc_args);
    if(!m_vlc_instance) {
        QMessageBox::information(this, "错误", "无法初始化VLC实例！");
        exit(EXIT_FAILURE);
    }

    // 3. 根据文件路径创建媒体对象
    // - 这个媒体对象可以用于后续的操作，如播放、暂停、获取媒体信息等
    m_media = libvlc_media_new_path(m_vlc_instance, filename.toStdString().c_str());

    // 4. 根据已有的媒体对象创建一个媒体播放器对象
    // - 利用媒体播放器对象，可以对关联的媒体资源进行播放、暂停、停止等操作
    m_media_player = libvlc_media_player_new_from_media(m_media);
    if(!m_media_player) {
        libvlc_release(m_vlc_instance);
        QMessageBox::information(this, "提示", "libvlc_media_player_new_from_media failed!");
        exit(EXIT_FAILURE);
    }

    // 5. 设置播放的窗口句柄
    // - 每个窗⼝都有⼀个唯⼀的句柄，⽤于标识该窗⼝。通过将这个窗⼝句柄传递给 libvlc_media_player_set_hwnd 函数，VLC 媒体播放器会将视频渲染到这个指定的窗⼝中
    // - 如果视频窗口已设置，立即关联到媒体播放器
    if(m_video_widget)
    {
        // 在主线程中设置窗口句柄
/*        // 使用QMetaObject，很容易导致死机，或者是UI操作被拦截
        //bool result = QMetaObject::invokeMethod(this, [this]()
        {
            libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
            // 添加windows API SetParent调用，帮助VLC正确识别窗口消息
            HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
            if(vlcHwnd)
            {
                SetParent(vlcHwnd, (HWND)m_video_widget->winId());
                // 设置窗口样式
                SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
                // 最大化VLC播放窗口
                ShowWindow(vlcHwnd, SW_SHOWMAXIMIZED);
                //SetWindowPos(vlcHwnd, NULL, 0, 0, m_video_widget->width(), m_video_widget->height(), SWP_NOZORDER);
            }
        }, Qt::QueuedConnection); // 移除超时参数, 溢出Blocking限制，避免调用线程阻塞等待，需要COM组件已经正确初始化
        if(!result)
        {
            log_info("Failed to invoke method to set VLC window handle");
        }
*/
/*        // 使用QTimer::singleShot在主线程空闲时执行,UI操作同样被拦截
        QTimer::singleShot(0, this, [this]()
        {
            HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
            if (SUCCEEDED(hr) || hr == S_FALSE)
            {
                libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
                HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
                if(vlcHwnd)
                {
                    SetParent(vlcHwnd, (HWND)m_video_widget->winId());
                    SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
                    ShowWindow(vlcHwnd, SW_SHOWMAXIMIZED);
                }
                if (SUCCEEDED(hr))
                {
                    CoUninitialize();
                }
            }
        });
*/
        libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
        // 在设置窗口句柄后添加
        HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
        if (!vlcHwnd) {
            log_info("Failed to get VLC render window handle");
        }
        QMessageBox::information(this, "已加载好文件", "请点击播放按钮");
    }
    else
    {
        QMessageBox::warning(this, "警告", "未设置视频播放窗口！");
    }

    // 6. 设置播放器的事件管理注册器
    // - 注册事件回调函数libvlc_event_attach，参数：(1)指向事件管理器的指针m_event_manager、(2)监听的事件类型，是枚举值、(3)事件发生时所触发的回调函数、(4)用户自定义数据，可以传送给回调函数参数
//    m_event_manager = libvlc_media_event_manager(m_media);
    m_event_manager = libvlc_media_player_event_manager(m_media_player);    // 此处不应注册到媒体对象，而应该注册到媒体播放器对象
    if(m_event_manager)
    {
        libvlc_event_attach(m_event_manager,
                            libvlc_MediaPlayerPositionChanged,
                            vlc_callback,
                            this);
        libvlc_event_attach(m_event_manager,
                            libvlc_MediaPlayerAudioVolume,
                            vlc_callback,
                            this);
//        // 添加全屏事件注册
//        libvlc_event_attach(m_event_manager,
//                            libvlc_MediaPlayerFullscreen,
//                            vlc_callback,
//                            this);
        log_info("event_manager set over!");
    }

    // - 获取媒体的总时间
    if(m_media)
    {
        libvlc_media_parse(m_media);    // 过时函数，不推荐使用
//        libvlc_media_parse_with_options(m_media, libvlc_media_parse_network, -1);  // 使用推荐的替代函数(第2个参数：指定是否解析网络媒体；第3个参数：默认超时时间);
        m_duration_seconds = libvlc_media_get_duration(m_media) / 1000;

        // 使用Qstring进行字符拼接
        QString logMessage = QString("total time: %1 seconds").arg(m_duration_seconds);
        log_info(logMessage.toUtf8().constData());
    }

}

// 开始播放
void VLCWidget::on_playbtn_clicked()
{
    log_info("");
    libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
    qDebug() << "state: " << state;
    if(state == libvlc_Paused || state == libvlc_Stopped || state == libvlc_NothingSpecial)
    {
        libvlc_media_player_play(m_media_player);
    }
}

// 暂停播放
void VLCWidget::on_pausebtn_clicked()
{
    log_info("");
    libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
    if(state == libvlc_Playing) {
        libvlc_media_player_pause(m_media_player);
    }
    //libvlc_media_player_pause(m_media_player);
}

// 在vlcwidget.cpp中添加释放事件绑定的函数
void VLCWidget::unbind_events()
{
    if(m_event_manager)
    {
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
        m_event_manager = nullptr; // 避免重复解绑
    }
}

// 停止播放
void VLCWidget::on_stopbtn_clicked()
{
    log_info("");
    libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
    if(state == libvlc_Playing || state == libvlc_Paused)
    {
        libvlc_media_player_stop(m_media_player);
        unbind_events(); // 停止后解绑事件
    }
}

//// 设置部件：时间进度条
//void VLCWidget::on_set_timer_slider_value(int value)
//{
//    emit set_timer_slider_value(value);
//}

//// 设置部件：时间显示
//void VLCWidget::on_set_timer_text(const QString& text)
//{
//    emit set_timer_text(text);
//}

//// 设置部件：音量滑动条
//void VLCWidget::on_set_volume_slider_value(int value)
//{
//    emit set_volume_slider_value(value);
//}
