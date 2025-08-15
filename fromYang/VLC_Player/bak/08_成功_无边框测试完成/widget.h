#ifndef WIDGET_H
#define WIDGET_H

#include "cframelesswidget.h"
#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QSlider;
class QLabel;
class VLCWidget;
class CTitleBar;
//class CVolumeSliderDialog;
class CVolumeButton;

//class Widget : public QWidget
class Widget : public CFramelessWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // 初始化控件
    void initialize_basic_UI();
    void initialize_central_button();   // 菜单目前全部交给ctitlebar.h完成，现在initialize_central_button负责初始化播放栏的打开文件夹
    void initialize_control_panel();

    // 信号槽函数
    void connect_UI_controls();
    void connect_VLC_widget_signals();

    // 设置风格
    void apply_styles();

    // 解决报错问题：QWidget::paintEngine: Should no longer be called
    // - 代码直接或间接地调用了 QWidget::paintEngine() 函数
    // - 但是实测没有什么用
    virtual void paintEvent(QPaintEvent *event) override
    {
        QWidget::paintEvent(event); // 调用父类实现，避免警告
        Q_UNUSED(event);
    }

public slots:
    void on_title_bar_close();      // ctitlewindow 需要实现关闭标题栏的功能
    void on_hide_central_button();  // 中央播放按钮在执行播放功能后隐藏

private:
    VLCWidget               *m_vlc_widget;     // vlc实例
    CTitleBar               *m_title_bar;      // 标题栏实例（新增）

    QVBoxLayout             *m_main_layout;    // 主布局

    QWidget                 *m_control_window; // 控制按钮

    QPushButton             *m_central_play_button;          // 中央播放按钮
    QPushButton             *m_open_button;    // 打开文件按钮
    QPushButton             *m_play_button;    // 播放按钮
    QPushButton             *m_pause_button;   // 暂停按钮
    QPushButton             *m_stop_button;    // 停止按钮
    //QPushButton             *m_volume_button;  // 音量按钮，目前托管CVolumeButton处理
    CVolumeButton           *m_volume_button;  // 音量按钮

    QSlider                 *m_time_slider = nullptr;       // 时间进度条
    QLabel                  *m_time_label = nullptr;        // 时间标签
    //QSlider                 *m_volume_slider = nullptr;     // 音量滑块值，目前托管cvolumebutton处理
    //QLabel                  *m_volume_label = nullptr;      // 音量标签，目前托管cvolumebutton处理
    //CVolumeSliderDialog     *m_volume_slider_dialog;        // 音量滑块值

};
#endif // WIDGET_H
