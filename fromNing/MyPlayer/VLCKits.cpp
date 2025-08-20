#include "VLCKits.h"
#include <QDebug>

VLCKits::VLCKits(QObject *parent) : QObject(parent)
{
    _pInstance = nullptr;
    _pMediaPlayer = nullptr;

    // 初始化定时器
    _pTimer = new QTimer(this);
    // 设置定时器间隔为 1 秒（1000毫秒）
    _pTimer->setInterval(1000);
    // 将定时器的 timeout() 信号连接到我们新创建的 updateTime() 槽函数
    connect(_pTimer, &QTimer::timeout, this, &VLCKits::updateTime);
}

VLCKits::~VLCKits() {
    libvlc_media_player_release(_pMediaPlayer);
    libvlc_media_release(_pMedia);
    libvlc_release(_pInstance);
}

static void processPosition(VLCKits * pkits)
{
    //百分比
    float pos = libvlc_media_player_get_position(pkits->mediaPlayer());
    pkits->setTimeSliderPos(pos * 100);
    // libvlc_time_t totalSecs = pkits->durations();
    libvlc_time_t totalSecs = pkits->durationArr()[pkits->currentIndex()];
    //qDebug() << "total secs: " << totalSecs;
    libvlc_time_t curSecs = libvlc_media_player_get_time(pkits->mediaPlayer()) / 1000;
    //qDebug() << "cur secs: " << curSecs;
    int hh = curSecs / 3600;
    int mm = curSecs % 3600 / 60;
    int ss = curSecs % 60;
    int HH = totalSecs / 3600;
    int MM = totalSecs % 3600 / 60;
    int SS = totalSecs % 60;
    char buff[64] = {0};
    sprintf(buff, "%02d:%02d:%02d/%02d:%02d:%02d", hh, mm, ss, HH, MM, SS);
    QString str(buff);
    pkits->setTimeText(str);
}

static void processVolume(VLCKits * pkits)
{
    int val = libvlc_audio_get_volume(pkits->mediaPlayer());
    qDebug() << "volume:" << val;
    if(val == -1) {
        return;
    }
    pkits->setVolumePos(val);
}

static void processMediaChanged(VLCKits* pkits)
{
    qDebug() << "执行的媒体发生了变化: processMediaChanged()";
    pkits->addMediaIndex();
}


// 回调函数, 参数()
static void vlc_callback( const struct libvlc_event_t *p_event, void *p_data )
{
    VLCKits * pkits = static_cast<VLCKits*>(p_data);
    if(pkits) {
        switch(p_event->type) {
        case libvlc_MediaPlayerPositionChanged:// 播放位置变化时
            processPosition(pkits);            // 调用这个函数调整进度条
            break;
        case libvlc_MediaPlayerAudioVolume: // 音量变化时
            processVolume(pkits);           // 调用这个函数调整音量
            break;
        case libvlc_MediaPlayerMediaChanged: // 播放的媒体发生了变化
            processMediaChanged(pkits);
            break;
        }
    }
}

bool VLCKits::initVLC()
{
    _pInstance = libvlc_new(0, nullptr); // 创建一个新的VLC实例 _pInstance
    if(_pInstance) {
        _pMediaPlayer = libvlc_media_player_new(_pInstance); // 创建新的媒体播放器对象 _pMediaPlayer
        if(_pMediaPlayer) {
            _pEventManager = libvlc_media_player_event_manager(_pMediaPlayer); // 获取媒体播放器对象的事件管理器 _pEventManager
            if(_pEventManager) {
                //注册事件管理器的回调函数
                //1. 位置发生改变时
                libvlc_event_attach(_pEventManager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
                //2. 声音变化时
                libvlc_event_attach(_pEventManager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
                // 3. 媒体改变时
                libvlc_event_attach(_pEventManager, libvlc_MediaPlayerMediaChanged, vlc_callback, this);
                return true;
            } else {
                // 将媒体播放器对象和VLC实例释放
                libvlc_media_player_release(_pMediaPlayer);
                libvlc_release(_pInstance);
                return false;
            }
        } else {
            libvlc_release(_pInstance);
            return false;
        }
    } else {
        return false;
    }
}

bool VLCKits::play(const QStringList &names, void *hwnd)
{
    // 创建一个新的媒体列表播放器对象 _pMediaListPlayer
    _pMediaListPlayer = libvlc_media_list_player_new(_pInstance);
    if(!_pMediaListPlayer) {
        return false;
    }
    // 创建一个新的媒体列表对象
    _pMediaList = libvlc_media_list_new(_pInstance);
    if(!_pMediaList) {
        return false;
    }
    for(int i = 0; i < names.size(); ++i) {
        QString filename = names[i];
        filename = QDir::toNativeSeparators(filename);
        // 创建一个媒体对象
        _pMedia = libvlc_media_new_path(_pInstance, filename.toStdString().c_str());
        if(!_pMedia) {
            return false;
        }
        //将媒体对象添加到播放列表中
        libvlc_media_list_add_media(_pMediaList, _pMedia);
        //解析媒体元数据
        libvlc_media_parse(_pMedia);
        // 获得总时长
        libvlc_time_t durationSecs = libvlc_media_get_duration(_pMedia) / 1000;
        // 将媒体总时长存入链表中
        _durationArr.push_back(durationSecs);
        libvlc_media_release(_pMedia);
    }
    //媒体列表关联媒体列表播放器                   媒体列表播放器        媒体列表
    libvlc_media_list_player_set_media_list(_pMediaListPlayer, _pMediaList);
    //设置播放模式：列表循环播放                       媒体列表播放器           循环模式
    libvlc_media_list_player_set_playback_mode(_pMediaListPlayer, libvlc_playback_mode_loop);
    //媒体播放器关联媒体列表播放器(必须加)               媒体列表播放器      媒体播放器
    libvlc_media_list_player_set_media_player(_pMediaListPlayer, _pMediaPlayer);

    libvlc_media_player_set_hwnd(_pMediaPlayer, hwnd);//设置播放窗口句柄
    libvlc_media_list_player_play(_pMediaListPlayer);//开始播放
    // 播放成功后，启动定时器
    if (_pMediaPlayer && libvlc_media_player_play(_pMediaPlayer) == 0) {
        // 【新增】如果正在播放，启动定时器
        _pTimer->start();
        return true;
    }
    qDebug() << "播放失败*******???";
    return false;
}

void VLCKits::play()
{
    libvlc_state_t state = libvlc_media_player_get_state(_pMediaPlayer);
    if(state == libvlc_Paused || state == libvlc_Stopped || state == libvlc_NothingSpecial) {
        libvlc_media_player_play(_pMediaPlayer);
    }
}
void VLCKits::pause()
{
    libvlc_state_t state = libvlc_media_player_get_state(_pMediaPlayer);
    if(state == libvlc_Playing) {   
        _pTimer->stop();    // 暂停时，停止定时器
        libvlc_media_player_pause(_pMediaPlayer);
    }
}
void VLCKits::stop()
{
    libvlc_state_t state = libvlc_media_player_get_state(_pMediaPlayer);
    if(state == libvlc_Playing || state == libvlc_Paused) {
        _pTimer->stop(); // 停止时, 停止定时器
        libvlc_media_player_stop(_pMediaPlayer);
        //重置进度条的位置
        emit sigTimeSliderPos(0);
        emit sigTimeChanged(0, 0);
    }
}

void VLCKits::setTimeSliderPos(int value)
{ //发送信号
    emit sigTimeSliderPos(value);
}
void VLCKits::setTimeText(const QString &str)
{ //发送信号
    emit sigTimeText(str);

}
void VLCKits::setVolumePos(int value)
{
    emit sigVolumeSliderPos(value);
}
void VLCKits::setVolume(int value)
{
    libvlc_audio_set_volume(_pMediaPlayer, value);
}
void VLCKits::setPosition(int value)
{
    libvlc_media_player_set_position(_pMediaPlayer, value / 100.0);
}

void VLCKits::addMediaIndex() {
    ++_currentIndex;
    _currentIndex %= _durationArr.size();
}

void VLCKits::updateTime()
{
    if (_pMediaPlayer) {
        // 获取当前播放时间和总时长，单位是毫秒
        qint64 currentTime = libvlc_media_player_get_time(_pMediaPlayer);
        qint64 totalTime = libvlc_media_player_get_length(_pMediaPlayer);

        // 发送信号，将这两个值传递出去
        emit sigTimeChanged(currentTime, totalTime);
    }
}
