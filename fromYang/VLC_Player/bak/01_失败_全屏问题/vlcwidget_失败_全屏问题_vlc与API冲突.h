#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <QWidget>
#include <vlc/vlc.h>  // 假设需要包含VLC头文件
#include <windows.h>

class QSlider;
class QLabel;

// 不建议重写，而是直接继承
// - Widget类主要负责UI布局
// - VLCWidget类专注于消息传递功能，不影响现有代码
class VLCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VLCWidget(QWidget *parent = nullptr);
    ~VLCWidget();

public:
    // 设置部件
    void set_video_widget(QWidget* widget);             // 设置video_widget
    // 以下函数复制到信号函数，通过位于widget.cpp的lambda函数实现功能
//    void set_timer_slider_value(int value);           // 设置时间进度条
//    void set_timer_text(const QString& text);         // 设置时间显示
//    void set_volume_slider_value(int value);          // 设置音量滑块值

    // 重写鼠标 / 键盘事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;     // 双击窗体达到全屏效果，时间处理函数应该在头文件中被设置为虚函数
    virtual void keyPressEvent(QKeyEvent *event) override;               // 按esc达到退出效果，时间处理函数应该在头文件中被设置为虚函数


    // 获得数据成员指针 / 数据成员状态
    libvlc_media_player_t* get_media_player(void) {  return m_media_player;  }
    libvlc_time_t get_duration_time(void) {  return m_duration_seconds;  }
    bool get_is_fullscreen() const {if(m_media_player) return libvlc_get_fullscreen(m_media_player); return false;}
    void check_fullscreen_state();  // 检查全屏状态

private:
    // 设置回调函数（处理小部件）
    static void vlc_callback( const struct libvlc_event_t *p_event, void *p_data);
    void unbind_events();    // 停止前解绑，使用This指针与数据成员，因此不能设置为静态函数
    // 以下两个函数禁用vlc的交互功能，直接启用windows API全屏控制逻辑
//    static BOOL CALLBACK EnumVLC(HWND hwnd, LPARAM lParam);
//    static void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time);

signals:
    // 以下为信号声明，调用流程为：
    // - 当媒体播放器的位置发生变化时，会触发libvlc_MediaPlayerPositionChanged事件，该函数位于void VLCWidget::on_openbtn_clicked()
    // - 在事件回调函数中，我们发送set_timer_slide_value 和 set_timer_text信号（信号仅需在vlcwidget.h中声明，无需实现）
    // - 这些信号被连接(connect)到“Widget”类中的lambda函数
    // - lambda函数会更新UI元素（进度条和时间标签）
    void set_timer_slider_value(int value);     // 设置时间进度条
    void set_timer_text(const QString& text);   // 设置时间显示
    void set_volume_slider_value(int value);    // 设置音量滑块值

public slots:
    void on_openbtn_clicked();
    void on_playbtn_clicked();
    void on_pausebtn_clicked();
    void on_stopbtn_clicked();

private:
    // VLC相关成员变量
    libvlc_instance_t       *m_vlc_instance = nullptr;      // vlc实例
    libvlc_media_t          *m_media = nullptr;             // 媒体对象
    libvlc_media_player_t   *m_media_player = nullptr;      // 媒体播放器
    libvlc_event_manager_t  *m_event_manager = nullptr;     // 事件管理器

    libvlc_time_t           m_duration_seconds = 0;         // 视频总时长

    // windows相关成员变量
    static HWND original_vlc_parent;                        // 原窗口

    // 其他必要成员
    QWidget                 *m_video_widget = nullptr;      // vlc播放窗口
    QTimer                  *m_fullscreen_timer = nullptr;  // 全屏播放定时器

    // 以下成员在widget中添加，保证布局效果 ; 功能的实现由信号 - 槽函数完成
    QSlider                 *m_time_slider = nullptr;       // 时间进度条
    QLabel                  *m_time_label = nullptr;        // 时间标签
    QSlider                 *m_volume_slider = nullptr;     // 音量滑块值
    QLabel                  *m_volume_label = nullptr;      // 音量标签

};

#endif // VLCWIDGET_H
