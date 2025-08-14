#ifndef VLCKITS_H
#define VLCKITS_H

#include <QObject>
#include <QDir>
#include <vlc/vlc.h>
#include <vector>
using std::vector; // 文件列表

class VLCKits : public QObject
{
    Q_OBJECT
public:
    explicit VLCKits(QObject *parent = nullptr);
    ~VLCKits();

    bool initVLC();                 // 初始化
    bool play(const QStringList &names , void * hwnd); // 加载并播放新的媒体文件
    void play();                    // 从暂停状态恢复
    void pause();                   // 暂停
    void stop();                    // 停止

    void setVolume(int value);      // 控制音量
    void setPosition(int value);    // 控制进度条

    // 访问器函数, 用来安全的访问私有成员变量, 在这里是播放器对象/秒数
    libvlc_media_player_t * mediaPlayer() const { return _pMediaPlayer; }
//    libvlc_time_t durations() const { return _totalSec; }

    // 用来解决业务逻辑(VLCKits)和UI界面(VLCWidget)之间的通信问题
    // 当需要修改UI界面的显示时，通过信号来触发，以下三个函数调用时就触发信号
    // 这种 "信号-槽" 的机制使得 VLCKits 完全不知道 VLCWidget 的存在，它只负责发出信号。而 VLCWidget 则连接这些信号并更新自己的 UI，实现了彻底的解耦。
    void setTimeSliderPos(int value);      // 当播放位置变化时，VLCKits 会发出这个信号，并携带当前的进度值。在 VLCWidget类里的槽函数可以连接到这个信号，然后更新进度条。
    void setTimeText(const QString & str); // 当播放时间需要更新时，VLCKits 会发出这个信号，并携带格式化后的时间字符串。VLCWidget里的槽函数可以连接到它，然后更新时间显示标签
    void setVolumePos(int value);          // 当音量变化时，VLCKits 会发出这个信号，VLCWidget 的槽函数可以连接它来更新音量滑块。

    // 文件列表相关成员函数
    void addMediaIndex();
    // 返回当前的媒体在vector里的下标
    int currentIndex() const { return _currentIndex; }
    const vector<libvlc_time_t> & durationArr() const
    { return _durationArr; }


signals://自定义信号
    void sigTimeSliderPos(int value);
    void sigTimeText(const QString & str);
    void sigVolumeSliderPos(int value);

private:
    libvlc_instance_t *     _pInstance = nullptr;
    libvlc_media_t *        _pMedia = nullptr;
    libvlc_media_player_t * _pMediaPlayer = nullptr;
    libvlc_event_manager_t *_pEventManager = nullptr;
    // libvlc_time_t           _totalSec = 0;  //一个文件的总时间

    // 文件列表相关数据人员
    libvlc_media_list_player_t * _pMediaListPlayer = nullptr;
    libvlc_media_list_t *        _pMediaList = nullptr;

    vector<libvlc_time_t>        _durationArr;  // 将一个媒体文件的总时长存放在一个vector里
    int _currentIndex = -1; // 表示当前播放的媒体下标
};

#endif // VLCKITS_H
