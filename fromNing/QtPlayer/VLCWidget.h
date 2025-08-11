#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <QWidget>
#include <vlc/vlc.h>

QT_BEGIN_NAMESPACE
namespace Ui { class VLCWidget; }
QT_END_NAMESPACE

class VLCWidget : public QWidget
{
    Q_OBJECT

public:
    VLCWidget(QWidget *parent = nullptr);
    ~VLCWidget();

// 定义了四个槽函数, 当对应的四个按钮被按下时, 将调用对应的槽函数
private slots:
    void on_btnOpen_clicked();  // on_???_clicker() 这种格式是 Qt Creator 默认的自动连接命名规范
    void on_btnPlayer_clicked();
    void on_btnPause_clicked();
    void on_btnStop_clicked();

// 四个对象指针
private:
    Ui::VLCWidget *ui;
    libvlc_instance_t*      _pinstance = nullptr;       // 指向一个vlc实例, libvlc实例是所有VLC操作的起点, 代表整个VLC运行时的环境
    libvlc_media_player_t*  _pmedia_player = nullptr;   // 此乃媒体播放器指针, 媒体播放器负责控制媒体文件的播放暂停等操作
    libvlc_media_t*         _pmedia = nullptr;          // 此乃媒体对象指针, 指向了一个特定的媒体文件或者流
};
#endif // VLCWIDGET_H
