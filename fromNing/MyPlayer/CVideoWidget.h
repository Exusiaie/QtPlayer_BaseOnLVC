#ifndef CVIDEOWIDGET_H
#define CVIDEOWIDGET_H

#include <QWidget>
// #include <memory>
#include "VLCKits.h"

class CVideoWidget : public QWidget
{
    Q_OBJECT

public:
    CVideoWidget(QWidget *parent = nullptr);
    ~CVideoWidget();


    // 重写 鼠标双击事件 处理函数 (Qt事件处理的4个方法...)
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    //键盘按下事件
   void keyPressEvent(QKeyEvent *event) override;

   VLCKits* getVLCKits() const { return _pVLCKits; }


// 定义槽函数
public slots:
    void on_btnOpen_clicked();   // 处理打开文件并播放的逻辑 <- CMenuWidget
    void on_btnPlayer_clicked(); // 播放 <-
    void on_btnPause_clicked();  // 暂停 <- CBottomCrtlBar
    void on_btnStop_clicked();   // 停止 <-
// 使用滑块控制视频进度和音量
    void on_playSlider_sliderMoved(int position);   // 使用滑块控制视频进度
    void on_volumeSlider_sliderMoved(int position); //  使用滑块控制音量
// 响应VLCKits的信号
//    void on_sigTimeSliderPos(int value);
//    void on_sigTimeText(const QString& str); // ?
//    void on_sigVolumeSliderPos(int value);
// 全屏按钮
    void on_btnFullScreen_clicked(); // 全屏 <- CBottomCrtlBar



signals:
    void sig_playsstatus(bool playstatus);
    void sigTimeChanged(qint64 current, qint64 total);


private:

    VLCKits                 *_pVLCKits;


};

#endif // CVIDEOWIDGET_H
