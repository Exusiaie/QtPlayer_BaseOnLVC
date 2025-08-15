// ... existing code ...
#ifndef CBUTTOMBAR_H
#define CBUTTOMBAR_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CVolumeButton;

class CButtomBar : public QWidget
{
    Q_OBJECT
public:
    explicit CButtomBar(QWidget *parent = nullptr);

    // 提供访问控件的方法
    QPushButton* getOpenButton() const;
    QPushButton* getPlayButton() const;
    QPushButton* getPauseButton() const;
    QPushButton* getStopButton() const;
    QSlider* getTimeSlider() const;
    QLabel* getTimeLabel() const;
    CVolumeButton* getVolumeButton() const;

signals:
    // 转发控件信号
    void openButtonClicked();
    void playButtonClicked();
    void pauseButtonClicked();
    void stopButtonClicked();
    void timeSliderMoved(int value);

private:
    QPushButton *m_open_button;    // 打开文件按钮
    QPushButton *m_play_button;    // 播放按钮
    QPushButton *m_pause_button;   // 暂停按钮
    QPushButton *m_stop_button;    // 停止按钮
    QSlider *m_time_slider;        // 时间进度条
    QLabel *m_time_label;          // 时间标签
    CVolumeButton *m_volume_button; // 音量按钮

private slots:
    // 处理控件信号
    void onOpenButtonClicked();
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();
    void onTimeSliderMoved(int value);
};

#endif // CBUTTOMBAR_H
