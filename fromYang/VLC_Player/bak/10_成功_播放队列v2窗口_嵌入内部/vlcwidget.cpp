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
#include <QCoreApplication>

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

VLCWidget::VLCWidget(QWidget *parent)
    : QWidget(parent)
    , m_vlc_instance(nullptr)
    , m_media(nullptr)
    , m_media_player(nullptr)
    , m_event_manager(nullptr)
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

    unbind_events();          // 解绑vlc事件

    // 1. 先释放最高层的"列表播放器"（它依赖media_player和media_list）
    log_info("开始释放m_media_list_player"); // 新增
    if (m_media_list_player)
    {
        libvlc_media_list_player_stop(m_media_list_player); // 停止列表播放
        //libvlc_media_list_player_release(m_media_list_player);    // 此处提前析构会导致引用计数 -1
        m_media_list_player = nullptr;
        log_info("m_media_list_player实例已销毁");
    }

    // 2. 释放"单个播放器"（它依赖media和vlc_instance）
    log_info("开始释放m_media_player");
    if (m_media_player)
    {
        libvlc_media_player_stop(m_media_player);
        log_info("m_media_player播放已停止");

//        libvlc_media_player_release(m_media_player);
        m_media_player = nullptr;
        log_info("m_media_player播放器实例已释放");
    }

    // 3. 释放"媒体列表"（它依赖多个media）
    log_info("开始释放m_media_list");
    if (m_media_list)
    {
        libvlc_media_list_release(m_media_list);
        m_media_list = nullptr;
        log_info("m_media_list实例已销毁");
    }

    // 4. 释放"单个媒体"（它仅依赖vlc_instance）
    log_info("开始释放m_media");
    if (m_media)
    {
        log_info("准备调用libvlc_media_release");
        libvlc_media_release(m_media);
        m_media = nullptr;
        log_info("libvlc_media_release实例已销毁"); // 看是否能打印到这行
    }

    // 5. 最后释放最底层的"VLC全局实例"（所有对象的基础）
    log_info("开始释放m_vlc_instance");
    if (m_vlc_instance)
    {
        log_info("准备调用libvlc_release");
        libvlc_release(m_vlc_instance);
        m_vlc_instance = nullptr;
        log_info("m_vlc_instance实例已销毁"); // 看是否能打印到这行
    }

    log_info("VLCWidget析构完成");
//    if (m_fullscreen_timer) {
//        m_fullscreen_timer->stop();
//        delete m_fullscreen_timer;
//        m_fullscreen_timer = nullptr;
//    }
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

libvlc_time_t VLCWidget::get_duration_time(void)
{
    if (m_current_index >= 0 && m_current_index < m_duration_arr.size())
    {
        return m_duration_arr[m_current_index];
    }
    return 0;
}

// 双击全屏 : 未实现，暂时禁掉功能
void VLCWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
/*    // vlc全屏切换与Qt窗口管理存在冲突，失效
    // 报错：drawable window warning: unsupported control query 2 | main vout display error: Failed to set fullscreen
    // VLC原生的全屏控制API在当前环境中存在兼容性问题
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
/*    // 全部交给Qt自身的窗口管理功能实现全屏效果，失败
    log_info("Mouse double click event received");

    if (!m_media_player || !m_video_widget)
    {
        event->accept();
        return;
    }

    // 切换Qt窗口的全屏状态
    bool isFullScreenNow = this->isFullScreen();

    if (isFullScreenNow)
    {
        this->showNormal();
        log_info("Exited fullscreen mode (Qt)");
    }
    else
    {
        this->showFullScreen();
        log_info("Entered fullscreen mode (Qt)");
    }

    // 强制调整VLC视频窗口
    resizeVlcWindow();

    // 阻止事件传递给VLC
    event->accept();
    // 不要调用QWidget::mouseDoubleClickEvent(event);
*/
/*    // 舍弃vlc全屏切换与Qt，改为由windows API接管
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
*/
}

// 键盘全屏 : 未实现，暂时禁掉功能
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
/*    // 退出全屏功能交给Qt实现，并且vlc调整窗口大小
    if(event->key() == Qt::Key_Escape && this->isFullScreen())
    {
        this->showNormal();
        log_info("Exited fullscreen via Escape (Qt)");
        resizeVlcWindow();
        event->accept();
        return;
    }

    // 其它按键事件交给父类处理
    QWidget::keyPressEvent(event);
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

    // 其它按键时间交给父类处理
    QWidget::keyPressEvent(event);
*/
/*    // 退出全屏功能交给windows API实现
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
*/
}

// 4. 添加辅助函数调整VLC窗口大小
void VLCWidget::resizeVlcWindow()
{
    if (m_media_player && m_video_widget)
    {
        HWND vlcHwnd = (HWND)libvlc_media_player_get_hwnd(m_media_player);
        if (vlcHwnd && IsWindow(vlcHwnd))
        {
            // 获取m_video_widget的客户区大小
            RECT rect;
            GetClientRect((HWND)m_video_widget->winId(), &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            // 调整VLC窗口大小和位置
            SetWindowPos(vlcHwnd, NULL, 0, 0, width, height, SWP_NOZORDER);
            log_info(QString("Resized VLC window to %1x%2").arg(width).arg(height).toUtf8().constData());

            // 确保VLC窗口是子窗口并正确显示
            SetParent(vlcHwnd, (HWND)m_video_widget->winId());
            SetWindowLong(vlcHwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
            ShowWindow(vlcHwnd, SW_SHOW);
        }
    }
}

/*// 检查是否为全屏
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
*/

// 被动接受音量
void VLCWidget::process_volume(VLCWidget* vlcwidget)
{

    int val = libvlc_audio_get_volume(vlcwidget->get_media_player());
    //log_info(QString(">>> volume: %1%").arg(val));
    qDebug() << ">>> volume:" << val;
    if(val == -1) {
        return;
    }
    vlcwidget->set_volume_slider_value(val);
}

// 主动改变音量
void VLCWidget::process_media_changed(VLCWidget* vlcwidget)
{
    log_info(">>>>> processMediaChanged()");
    vlcwidget->add_media_index();
}

// vlc回调事件处理函数
void VLCWidget::vlc_callback(const struct libvlc_event_t *p_event, void *p_data)
{
    log_info("vlc_callback开始");
    VLCWidget * p = static_cast<VLCWidget*>(p_data);
    if(p)
    {
        switch (p_event->type)
        {
            case libvlc_MediaPlayerPositionChanged:
            {
                log_info("时间进度条处理");
                // 获取到的是一个百分比
                float pos = libvlc_media_player_get_position(p->get_media_player());
//                p->set_timer_slider_value(static_cast<int>(pos * 100));
                emit p->set_timer_slider_value(static_cast<int>(pos * 100));    // 发送信号
                // 设置视频的时间
                qint64 totalSec = p->get_duration_time();
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
                log_info("声音处理");
                int val = libvlc_audio_get_volume(p->get_media_player());
                emit p->set_volume_slider_value(val);
                break;
            }
            case libvlc_MediaPlayerMediaChanged:
            {
                log_info("媒体已更改");
                process_media_changed(p);
                break;
            }
        }
    }
    log_info("vlc_callback完成");
}

bool VLCWidget::play(const QStringList &names, void *hwnd)
{
    log_info("play开始");
    // 1.设置列表播放器
    // - 创建
    m_media_list_player = libvlc_media_list_player_new(m_vlc_instance);
    if(!m_media_list_player) {log_error("m_media_list_player 创建失败"); return false; }
    log_info("m_media_list_player 创建成功");

    m_media_list = libvlc_media_list_new(m_vlc_instance);
    if(!m_media_list) {log_error("m_media_list 创建失败"); return false;}
    log_info("m_media_list 创建成功");


    m_media_paths.clear();  // 清空媒体路径列表

    for(auto filename : names) {
        log_info("for循环进入");
        // - 必须执行这一步，否则会报错
        filename = QDir::toNativeSeparators(filename);

        // - 保存媒体路径
        m_media_paths.append(filename);

        // - 创建媒体对象：可以用于后续的操作，如播放、暂停、获取媒体信息等
        m_media = libvlc_media_new_path(m_vlc_instance, filename.toStdString().c_str());
        if(!m_media) {log_error("m_media 创建失败"); return false;}
        libvlc_media_list_add_media(m_media_list, m_media); // - 将媒体添加到播放列表中
        log_info("媒体添加至播放列表");

        // - 获取媒体的总时间
        libvlc_media_parse(m_media);    // 过时函数，不推荐使用
        // - 使用推荐的替代函数(第2个参数：指定是否解析媒体；第3个参数：默认超时时间)
        // - 比较搞笑的是，这个函数反而不能获得正确的时间
        //libvlc_media_parse_with_options(m_media, libvlc_media_parse_local, 5000);
        libvlc_time_t current_duration_secs = libvlc_media_get_duration(m_media) / 1000;
        m_duration_arr.push_back(current_duration_secs);
        log_info(QString("total time: %1 seconds").arg(current_duration_secs).toUtf8().constData());

        libvlc_media_release(m_media);
    }
    log_info("for循环结束");

    // - 发送媒体列表更新信号
    emit media_list_updated();

    // 2. 根据已有的媒体对象创建一个媒体播放器对象
    // - 利用媒体播放器对象，可以对关联的媒体资源进行播放、暂停、停止等操作
    libvlc_media_list_player_set_media_list(m_media_list_player, m_media_list);
    log_info("成功关联m_media_list_player, m_media_list");

    // 3. 设置播放模式：列表循环播放
    libvlc_media_list_player_set_playback_mode(m_media_list_player, libvlc_playback_mode_loop);
    log_info("成功设置列表循环播放");

    // 4. 媒体列表播放器关联媒体播放器(必须加)
    if (!m_media_player)
    {
        m_media_player = libvlc_media_player_new(m_vlc_instance);
        if (!m_media_player) {
            log_error("m_media_player 创建失败");
            return false;
        }
    }
    libvlc_media_list_player_set_media_player(m_media_list_player, m_media_player);
    log_info("成功关联m_media_list_player, m_media_player");

    // 5. 设置播放的窗口句柄
    // - 每个窗⼝都有⼀个唯⼀的句柄，⽤于标识该窗⼝。通过将这个窗⼝句柄传递给 libvlc_media_player_set_hwnd 函数，VLC 媒体播放器会将视频渲染到这个指定的窗⼝中
    // - 如果视频窗口已设置，立即关联到媒体播放器
    libvlc_media_player_set_hwnd(m_media_player, hwnd);     // 设置播放窗口
    log_info("成功设置播放窗口");

    // 6. 关闭屏幕居中的按钮
    emit hide_central_button();

    // 7. 开始播放
    libvlc_media_list_player_play(m_media_list_player);     // 开始播放
    m_current_index = 0;                                    // 初始化当前索引
    log_info("开始播放");

    return true;
}

void VLCWidget::on_openbtn_clicked()
{

/*    // 0. 初始化COM组件，没有必要，Qt自己会想办法初始化COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr) && hr != S_FALSE)
    {
        QMessageBox::critical(this, "错误", "COM组件初始化失败!");
        return;
    }
*/

    // 1. 打开文件
    log_info("openbtn开始");
//    CoInitialize(NULL);         // Windows平台兼容问题，初始化COM组件
    QStringList filenames = QFileDialog::getOpenFileNames    // Qt标准GUI组件
    (
        this,                               // 指向父窗口的指针
        tr("打开文件"),                     // 文件对话框的标题
        QDir::currentPath(),                // 对话框打开时的初始目录
        "视频文件(*.mp4);;"                 // 文件过滤器，限定用户只能选择mp4或avi格式的视频
        "视频文件(*.avi);;"
    );
    if (filenames.isEmpty()) return;

    // 释放之前的VLC实例
    // - 解决频繁切换打开文件的问题
    if (m_media_list_player) {
        libvlc_media_list_player_stop(m_media_list_player);
        libvlc_media_list_player_release(m_media_list_player);
        m_media_list_player = nullptr;
    }
    if (m_media_list) {
        libvlc_media_list_release(m_media_list);
        m_media_list = nullptr;
    }
    if (m_media_player) {
        libvlc_media_player_stop(m_media_player);
        libvlc_media_player_release(m_media_player);
        m_media_player = nullptr;
    }
    log_info("openbtn-释放之前的vlc实例完成");

    // 2. 创建vlc实例
    // 获取程序运行目录（.exe所在目录）
    QString appDir = QCoreApplication::applicationDirPath();
    // 构建插件目录的相对路径（运行目录下的plugins文件夹）
    QString pluginPath = appDir + "/plugins";
    // 转换为C字符串（VLC接口要求）
    QByteArray pluginPathBytes = pluginPath.toUtf8();

    const char* vlc_args[] =
    {

        "--ignore-config",      // 忽略全局配置文件
        "--quiet",              // 静默模式（减少日志）
        "--directx-use-sysmem", // 使用系统内存而非显存（解决windows平台下某些显卡兼容性问题）
        "--avcodec-hw=any"      // 启用硬件加速（可选）
        "--no-video-title-show",// 禁用标题显示
        "--no-snapshot-preview",// 禁用快照预览
        "--no-osd",             // 禁用屏幕显示
        "--no-fullscreen",      // 禁用VLC全屏
        "--no-video-deco",      // 禁用视频窗口装饰（避免VLC窗口自带边框干扰）
        "--no-embedded-video",  // 禁用嵌入式视频处理（防止VLC接管窗口布局）
        "--video-on-top",       // 视频窗口置顶
    };
        //"--directx-device=desktop", // 使用桌面设备
        //"--qt-fullscreen-screennumber=0",  // 指定全屏显示器
        //"--aout=directsound",   // 强制使用 directsound 音频输出，解决报错：mmdevice audio output error: cannot initialize COM错误
        //"--no-disable-screensaver", // 禁用屏幕保护程序
        //"--no-qt-video-autoresize",  // 禁用视频自动调整大小（不知道是不是与当前qt设置冲突，因此不选）
        //"--no-plugins-cache", // 禁用插件缓存（若问题仍存在则关闭）
        //"--avcodec-threads=2",  // 限制解码线程数（在windows平台下减少资源竞争，实测添加后容易死锁）

        //"--video-x11-display=:0", // 设置X11显示（该版本不支持）
        //"--directx-force-yuv",  // 强制YUV渲染（该版本不支持）
        //"--plugin-path", pluginPathBytes.constData(),  // 相对路径生效（VLC 3.x已不支持）
        //"--audio-buffer=500",   // 增加音频缓冲区（全局参数无效）
        //"--wasapi-buffer-duration=500",  // 针对wasapi模块设置缓冲时长（单位：毫秒）(同样不支持)
        //"--no-drop-late-frames",// 尝试不丢弃延迟帧

//    "--aout=wasapi",        // 使用更稳定的WASAPI音频输出
//    "--clock-jitter=100",    // 允许更大的时钟抖动（减少同步严格性）
//    "--network-caching=500", // 增加网络缓冲（本地文件也适用）
//    "--rtsp-frame-buffer-size=1000000", // 增加帧缓冲区大小

    int argc = sizeof(vlc_args) / sizeof(vlc_args[0]);
    m_vlc_instance = libvlc_new(argc, vlc_args);
    if (!m_vlc_instance) {
        log_error("VLC实例创建失败");
        return;
    }
    log_info("openbtn-创建新的vlc实例完成");

    // 3. 调用play函数
    play(filenames, (void*)m_video_widget->winId());
    log_info("openbtn-创建play函数完成");

/*    // 4. 初始化定时器并连接（新增）
    if (!m_fullscreen_timer)
    {
        m_fullscreen_timer = new QTimer(this);
        connect(m_fullscreen_timer, &QTimer::timeout, this, &VLCWidget::check_fullscreen_state);
        m_fullscreen_timer->start(500); // 每500毫秒检查一次
    }
*/

    // 5. 设置播放器的事件管理注册器
    // - 注册事件回调函数libvlc_event_attach，参数：(1)指向事件管理器的指针m_event_manager、(2)监听的事件类型，是枚举值、(3)事件发生时所触发的回调函数、(4)用户自定义数据，可以传送给回调函数参数
//    m_event_manager = libvlc_media_event_manager(m_media);
    m_event_manager = libvlc_media_player_event_manager(m_media_player);    // 此处不应注册到媒体对象，而应该注册到媒体播放器对象
    if(m_event_manager)
    {
        // 注册媒体播放器的事件处理器
        // 1. 位置发生改变时
        libvlc_event_attach(m_event_manager,
                            libvlc_MediaPlayerPositionChanged,
                            vlc_callback,
                            this);

        // 2. 声音变化时
        libvlc_event_attach(m_event_manager,
                            libvlc_MediaPlayerAudioVolume,
                            vlc_callback,
                            this);
//        // 3. 添加全屏事件注册  // 在3.0.18版本查无此函数
//        libvlc_event_attach(m_event_manager,
//                            libvlc_MediaPlayerFullscreen,
//                            vlc_callback,
//                            this);
        // 4. 媒体改变时(添加的代码)
        libvlc_event_attach(m_event_manager,
                            libvlc_MediaPlayerMediaChanged,
                            vlc_callback,
                            this);

        log_info("设置事件处理器完成");
    }

    log_info("openbtn完成");
}

// 开始播放
void VLCWidget::on_playbtn_clicked()
{
    if(m_media_player)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
        log_info(QString("state: %1%").arg(state).toUtf8().data());
        if(state == libvlc_Paused || state == libvlc_Stopped || state == libvlc_NothingSpecial)
        {
            libvlc_media_player_play(m_media_player);
        }
    }
    else
    {
        QMessageBox::information(nullptr, "提示", "请先打开媒体文件", QMessageBox::Ok);        // 显示友好提示
        QTimer::singleShot(500, this, &VLCWidget::on_openbtn_clicked);                     // 短暂延迟后自动触发打开文件
    }
}

// 暂停播放
void VLCWidget::on_pausebtn_clicked()
{
    if(m_media_player)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_media_player);
        log_info(QString("state: %1%").arg(state).toUtf8().data());
        if(state == libvlc_Playing) {
            libvlc_media_player_pause(m_media_player);
        }
    }
    else
    {
        QMessageBox::information(nullptr, "提示", "请先打开媒体文件", QMessageBox::Ok);        // 显示友好提示
        QTimer::singleShot(500, this, &VLCWidget::on_openbtn_clicked);                     // 短暂延迟后自动触发打开文件
    }
}

// 在vlcwidget.cpp中添加释放事件绑定的函数
void VLCWidget::unbind_events()
{
    // 逐个解绑时间
    if(m_media_player && m_event_manager)
    {
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
        libvlc_event_detach(m_event_manager, libvlc_MediaPlayerMediaChanged, vlc_callback, this);
        m_event_manager = nullptr; // 避免重复解绑
        log_info("所有VLC事件已解绑");
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

// 新增按索引播放媒体方法
void VLCWidget::on_play_media_by_index(int index)
{
    log_info(QString("按索引播放媒体: %1").arg(index).toUtf8().data());
    if (index >= 0 && index < m_media_paths.size() && m_media_list_player)
    {
        // 设置当前索引
        m_current_index = index;
        // 播放指定索引的媒体
        libvlc_media_list_player_set_media_list(m_media_list_player, m_media_list);
        libvlc_media_list_player_play_item_at_index(m_media_list_player, index);
        log_info(QString("开始播放索引 %1 的媒体").arg(index).toUtf8().data());
    }
    else
    {
        log_error("无效的媒体索引或媒体列表播放器未初始化");
    }
}
