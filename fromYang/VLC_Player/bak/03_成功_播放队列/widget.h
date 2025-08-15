#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QSlider;
class QLabel;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // 解决报错问题：QWidget::paintEngine: Should no longer be called
    // - 代码直接或间接地调用了 QWidget::paintEngine() 函数
    virtual void paintEvent(QPaintEvent *event) override
    {
        QWidget::paintEvent(event); // 调用父类实现，避免警告
        Q_UNUSED(event);
    }

private:
    QVBoxLayout             *m_main_layout;    // 主布局

    QPushButton             *m_open_button;    //打开文件按钮
    QPushButton             *m_play_button;    //播放按钮
    QPushButton             *m_pause_button;   //暂停按钮
    QPushButton             *m_stop_button;    //停止按钮

    QSlider                 *m_time_slider = nullptr;       // 时间进度条
    QLabel                  *m_time_label = nullptr;        // 时间标签
    QSlider                 *m_volume_slider = nullptr;     // 音量滑块值
    QLabel                  *m_volume_label = nullptr;      // 音量标签
};
#endif // WIDGET_H
