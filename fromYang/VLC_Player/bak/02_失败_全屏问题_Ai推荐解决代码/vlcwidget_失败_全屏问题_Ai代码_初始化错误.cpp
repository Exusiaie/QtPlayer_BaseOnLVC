#include "vlcwidget.h"

#include <qevent.h>
#include <windows.h>
#include <objbase.h>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSlider>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication> // 新增头文件

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
    , m_is_fullscreen(false) // 新增全屏状态标记
    , m_time_slider(nullptr)
    , m_time_label(nullptr)
    , m_volume_slider(nullptr)
    , m_volume_label(nullptr)
{
    log_info("");
}

VLCWidget::~VLCWidget()
{
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

void VLCWidget::set_video_widget(QWidget *widget)
{
    m_video_widget = widget;

    if(m_video_widget)
    {
        m_video_widget->setAttribute(Qt::WA_OpaquePaintEvent);
        m_video_widget->setAttribute(Qt::WA_NoSystemBackground);
        m_video_widget->setAttribute(Qt::WA_PaintOnScreen);
        m_video_widget->setFocusPolicy(Qt::StrongFocus);

        HWND hwnd = (HWND) m_video_widget->winId();
        EnableWindow(hwnd, TRUE);

        if(m_media_player)
        {
            QMetaObject::invokeMethod(this, [this](){
                libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
                // 确保VLC窗口正确嵌入
                HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
                if(vlcHwnd) {
                    SetParent(vlcHwnd, (HWND)m_video_widget->winId());
                    SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
                    // 调整大小以匹配父窗口
                    RECT rect;
                    GetClientRect((HWND)m_video_widget->winId(), &rect);
                    SetWindowPos(vlcHwnd, NULL, 0, 0, rect.right, rect.bottom, 
                                SWP_NOZORDER | SWP_NOACTIVATE);
                }
            }, Qt::QueuedConnection);
        }

        QString logMessage = QString("Video widget set with handle: %1").arg(m_video_widget->winId());
        log_info(logMessage.toUtf8().constData());
    }
}

// 修复全屏切换逻辑
void VLCWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    log_info("Mouse double click event received");

    if (!m_media_player || !m_video_widget)
    {
        event->accept();
        return;
    }

    // 切换全屏状态
    m_is_fullscreen = !m_is_fullscreen;
    HWND mainHwnd = (HWND)this->winId();
    HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);

    if (m_is_fullscreen) {
        // 保存当前窗口状态用于恢复
        GetWindowPlacement(mainHwnd, &m_prev_window_placement);
        
        // 进入全屏
        RECT screenRect;
        HWND hDesktop = GetDesktopWindow();
        GetWindowRect(hDesktop, &screenRect);
        
        // 设置主窗口全屏
        SetWindowPos(mainHwnd, HWND_TOPMOST, 
                    screenRect.left, screenRect.top,
                    screenRect.right - screenRect.left,
                    screenRect.bottom - screenRect.top,
                    SWP_SHOWWINDOW);
        
        // 调整VLC窗口
        if (vlcHwnd && IsWindow(vlcHwnd)) {
            SetParent(vlcHwnd, (HWND)m_video_widget->winId());
            SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
            SetWindowPos(vlcHwnd, NULL, 
                        screenRect.left, screenRect.top,
                        screenRect.right - screenRect.left,
                        screenRect.bottom - screenRect.top,
                        SWP_NOZORDER | SWP_NOACTIVATE);
        }
        log_info("Entered fullscreen mode");
    } else {
        // 恢复窗口状态
        SetWindowPlacement(mainHwnd, &m_prev_window_placement);
        ShowWindow(mainHwnd, SW_SHOWNORMAL);
        
        // 恢复VLC窗口
        if (vlcHwnd && IsWindow(vlcHwnd)) {
            RECT rect;
            GetClientRect((HWND)m_video_widget->winId(), &rect);
            SetWindowPos(vlcHwnd, NULL, 0, 0, 
                        rect.right - rect.left, 
                        rect.bottom - rect.top,
                        SWP_NOZORDER | SWP_NOACTIVATE);
        }
        log_info("Exited fullscreen mode");
    }

    event->accept();
    QWidget::mouseDoubleClickEvent(event);
}

void VLCWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && m_is_fullscreen)
    {
        // 退出全屏
        m_is_fullscreen = false;
        HWND mainHwnd = (HWND)this->winId();
        HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);

        // 恢复窗口状态
        SetWindowPlacement(mainHwnd, &m_prev_window_placement);
        ShowWindow(mainHwnd, SW_SHOWNORMAL);
        
        // 恢复VLC窗口
        if (vlcHwnd && IsWindow(vlcHwnd)) {
            RECT rect;
            GetClientRect((HWND)m_video_widget->winId(), &rect);
            SetWindowPos(vlcHwnd, NULL, 0, 0, 
                        rect.right - rect.left, 
                        rect.bottom - rect.top,
                        SWP_NOZORDER | SWP_NOACTIVATE);
        }

        log_info("Exited fullscreen mode via Escape key");
        event->accept();
        return;
    }
    QWidget::keyPressEvent(event);
}

void VLCWidget::check_fullscreen_state()
{
    // 移除VLC全屏状态检查，使用自定义的m_is_fullscreen状态
    if(m_media_player && m_video_widget)
    {
        if(m_is_fullscreen && !m_video_widget->isFullScreen())
        {
            m_video_widget->showFullScreen();
        }
        else if(!m_is_fullscreen && m_video_widget->isFullScreen())
        {
            m_video_widget->showNormal();
        }
    }
}

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
                float pos = libvlc_media_player_get_position(p->get_media_player());
                emit p->set_timer_slider_value(static_cast<int>(pos * 100));
                
                qint64 totalSec = p->get_duration_time();
                qint64 curSec = libvlc_media_player_get_time(p->get_media_player()) / 1000;
                
                // 增加边界检查，防止负数或超出范围的时间值
                if (curSec < 0) curSec = 0;
                if (totalSec <= 0) totalSec = 1; // 避免除以零
                if (curSec > totalSec) curSec = totalSec;

                int HH = totalSec / 3600;
                int MM = (totalSec - HH * 3600) / 60;
                int SS = totalSec - HH *3600 - MM * 60;
                
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

void VLCWidget::on_openbtn_clicked()
{
    log_info("");
    QString filename = QFileDialog::getOpenFileName
    (
        this,
        "请选择视频文件",
        "D:/",
        "视频文件(*.mp4 *.avi *.mkv *.flv);;所有文件(*.*)"
    );

    qDebug() << "filename:" << filename;
    if(filename.isEmpty()) {
        return;
    }
    filename = QDir::toNativeSeparators(filename);

    // 释放之前的资源
    if(m_media_player)
    {
        libvlc_media_player_stop(m_media_player);
        libvlc_media_player_release(m_media_player);
        m_media_player = nullptr;
    }
    if(m_media)
    {
        libvlc_media_release(m_media);
        m_media = nullptr;
    }
    if(m_vlc_instance)
    {
        libvlc_release(m_vlc_instance);
        m_vlc_instance = nullptr;
    }

    // 优化VLC参数，解决音频缓冲问题
    const char* vlc_args[] =
    {
        "--ignore-config",
        "--quiet",
        "--directx-use-sysmem",
        "--no-video-title-show",
        "--no-snapshot-preview",
        "--no-osd",
        "--no-fullscreen",
        "--aout=wasapi", // 使用WASAPI替代directsound改善音频
        "--audio-buffer=200", // 增加音频缓冲
        "--network-caching=300", // 增加网络缓冲
        "--clock-jitter=0", // 减少时钟抖动
        "--clock-synchro=0" // 禁用时钟同步
    };

    m_vlc_instance = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]), vlc_args);
    if(!m_vlc_instance) {
        QMessageBox::critical(this, "错误", "无法初始化VLC实例！");
        return;
    }

    m_media = libvlc_media_new_path(m_vlc_instance, filename.toStdString().c_str());
    if(!m_media) {
        QMessageBox::critical(this, "错误", "无法创建媒体对象！");
        libvlc_release(m_vlc_instance);
        return;
    }

    m_media_player = libvlc_media_player_new_from_media(m_media);
    if(!m_media_player) {
        QMessageBox::critical(this, "错误", "无法创建媒体播放器！");
        libvlc_media_release(m_media);
        libvlc_release(m_vlc_instance);
        return;
    }

    if(m_video_widget)
    {
        libvlc_media_player_set_hwnd(m_media_player, (void*)m_video_widget->winId());
        HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
        if (vlcHwnd) {
            SetParent(vlcHwnd, (HWND)m_video_widget->winId());
            SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
            RECT rect;
            GetClientRect((HWND)m_video_widget->winId(), &rect);
            SetWindowPos(vlcHwnd, NULL, 0, 0, rect.right, rect.bottom, SWP_NOZORDER);
        } else {
            log_info("Failed to get VLC render window handle");
        }
        QMessageBox::information(this, "提示", "已加载文件，请点击播放按钮");
    }
    else
    {
        QMessageBox::warning(this, "警告", "未设置视频播放窗口！");
    }

    m_event_manager = libvlc_media_player_event_manager(m_media_player);
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
        log_info("event_manager set over!");
    }

    if(m_media)
    {
        libvlc_media_parse_with_options(m_media, libvlc_media_parse_network, 5000); // 使用推荐函数并设置超时
        m_duration_seconds = libvlc_media_get_duration(m_media) / 1000;
        QString logMessage = QString("total time: %1 seconds").arg(m_duration_seconds);
        log_info(logMessage.toUtf8().constData());
    }
}

void VLCWidget::on_playbtn_clicked()
{
    log_info("");
    if(!m_media_player) return;

    libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
    qDebug() << "state: " << state;
    if(state == libvlc_Paused || state == libvlc_Stopped || state == libvlc_NothingSpecial)
    {
        // 播放前确保音频输出正确初始化
        libvlc_audio_output_t *output = libvlc_audio_output_list_get(m_vlc_instance);
        if(output) {
            libvlc_audio_output_list_release(output);
        }
        libvlc_media_player_play(m_media_player);
    }
}

void VLCWidget::on_pausebtn_clicked()
{
    log_info("");
    if(m_media_player)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
        if(state == libvlc_Playing) {
            libvlc_media_player_pause(m_media_player);
        }
    }
}

void VLCWidget::unbind_events()
{
    if(m_event_manager)
    {
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
        m_event_manager = nullptr;
    }
}

void VLCWidget::on_stopbtn_clicked()
{
    log_info("");
    if(m_media_player)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
        if(state == libvlc_Playing || state == libvlc_Paused)
        {
            libvlc_media_player_stop(m_media_player);
            unbind_events();
        }
    }
}
