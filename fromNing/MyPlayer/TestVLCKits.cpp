#include "TestVLCKits.h"
#include <QDebug>
#include <QMessageBox>

TestVLCKits::TestVLCKits(QObject *parent)
    : QObject(parent)
{
    // 可以在这里进行一些初始化操作
}

void TestVLCKits::handlePlay()
{
    libvlc_state_t state = libvlc_media_player_get_state(_pMediaPlayer);
    if(state == libvlc_Paused || state == libvlc_Stopped || state == libvlc_NothingSpecial) {
        libvlc_media_player_play(_pMediaPlayer);
    }
}

void TestVLCKits::handleStop()
{
    libvlc_state_t state = libvlc_media_player_get_state(_pMediaPlayer);
    if(state == libvlc_Playing || state == libvlc_Paused) {
        libvlc_media_player_stop(_pMediaPlayer);
        //重置进度条的位置
       // emit sigTimeSliderPos(0);
    }
}

void TestVLCKits::handleFullScreen(){

}

