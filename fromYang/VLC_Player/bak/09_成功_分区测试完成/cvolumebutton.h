#ifndef CVOLUMEBUTTON_H
#define CVOLUMEBUTTON_H

#include "cvolumedialog.h"
#include <QPushButton>
#include <QLabel>

class CVolumeButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CVolumeButton(QWidget *parent = nullptr);
    ~CVolumeButton();

    CVolumeSliderDialog* getVolumeSliderDialog(void) { return _pvolumeSliderDlg; }
    void setVolumeValue(int volumeValue) { _volumeValue = volumeValue; }
    void setVolumeLabel(QString volumeLabel) { _volumeLabel->setText(volumeLabel); }

//signals:
//    void volumeChanged(int volumme);    // 音量变化信号

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
/*    void leaveEvent(QEvent *event) override;  */        // 注释掉，不再使用，此处使用定时器
    void timerEvent(QTimerEvent* event) override;         // 重写定时器函数
    void mousePressEvent(QMouseEvent* event) override;    // 音量按钮被按下时，调用mousePressEvent函数
//    void mouseReleaseEvent(QMouseEvent *event) override;

//    bool event(QEvent *event) override;
//    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void InitVolumeButton();
    void hideVolumeDialog();
//    int value(void){ return _volumeValue; }

private:
    CVolumeSliderDialog     *_pvolumeSliderDlg = nullptr;

    QLabel                  *_volumeLabel = nullptr;      // 添加音量标签
    int                     _volumeValue = 20;            // 音量值
    bool                    _isMute = false;              // 是否静音

    int                     _timerId = 0;                 // 定时器id
    bool                    _isRunning = false;           // 定时器开启的标志位
};

#endif // CVOLUMEBUTTON_H
