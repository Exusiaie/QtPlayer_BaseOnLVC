#ifndef TESTVLCKITS_H
#define TESTVLCKITS_H

#include <QObject>
#include <QDir>
#include <vlc/vlc.h>

class TestVLCKits : public QObject
{
    Q_OBJECT

public:
    explicit  TestVLCKits(QObject *parent = nullptr);

public slots:
    // 接收 CBottomCtrlBar 发来的信号的槽函数
    void handlePlay();
    void handleStop();
    void handleFullScreen();

private:
    libvlc_instance_t *     _pInstance = nullptr;
    libvlc_media_t *        _pMedia = nullptr;
    libvlc_media_player_t * _pMediaPlayer = nullptr;
    libvlc_event_manager_t *_pEventManager = nullptr;
    // libvlc_time_t           _totalSec = 0;  //一个文件的总时间

    // 文件列表相关数据人员
    libvlc_media_list_player_t * _pMediaListPlayer = nullptr;
    libvlc_media_list_t *        _pMediaList = nullptr;
};

#endif // TESTVLCKITS_H
