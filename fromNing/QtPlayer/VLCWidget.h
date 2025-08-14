#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <QWidget>
#include <memory>
#include "VLCKits.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VLCWidget; }
QT_END_NAMESPACE

class VLCKits;

class VLCWidget : public QWidget
{
    Q_OBJECT

public:
    VLCWidget(QWidget *parent = nullptr);
    ~VLCWidget();

    // 重写 鼠标双击事件 处理函数 (Qt事件处理的4个方法...)
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    //键盘按下事件
    void keyPressEvent(QKeyEvent *event) override;

// 定义槽函数, 当对应的四个按钮被按下时, 将调用对应的槽函数
// !!!!! 根据Qt的命名约定，on_对象名_信号名的格式会自动将信号连接到槽。!!!!!!!!
private slots:
    void on_btnOpen_clicked();  // on_???_clicker() 这种格式是 Qt Creator 默认的自动连接命名规范
    void on_btnPlayer_clicked();
    void on_btnPause_clicked();
    void on_btnStop_clicked();
// 使用滑块控制视频进度和音量
    void on_playSlider_sliderMoved(int position);
    void on_volumeSlider_sliderMoved(int position);
// 响应VLCKits的信号
    void on_sigTimeSliderPos(int value);
    void on_sigTimeText(const QString& str);
    void on_sigVolumeSliderPos(int value);
// 全屏按钮
    void on_btnFullScreen_clicked();


private:
    Ui::VLCWidget *ui;
    //VLCKits* _pVLCKits = nullptr; // VLCKits类的指针, 指向VLCKits的实例
    std::unique_ptr<VLCKits> _pVLCKits; // 将多个VLCKits类的指针存入容器中
};
#endif // VLCWIDGET_H
