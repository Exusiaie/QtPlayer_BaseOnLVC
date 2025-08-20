#ifndef CPLAYBUTTONGROUPWIDGET_H
#define CPLAYBUTTONGROUPWIDGET_H

#pragma once
#include "CVolumeButton.h"
#include <QWidget>
#include <QPushButton>
class CPlayButtonGroupWidget : public QWidget
{
    Q_OBJECT
public:
    CPlayButtonGroupWidget(QWidget *parent = Q_NULLPTR);
    ~CPlayButtonGroupWidget();

public slots:
    void setPlaying(bool playing); // 切换播放/暂停图标

signals:
    void sig_stop();
    void sig_pre();
    void sig_play();
    void sig_next();
    void sliderValueChanged(int value);
private:
    QPushButton* m_pStopButton = nullptr;
    QPushButton* m_pPreButton = nullptr;
    QPushButton* m_pPlayButton = nullptr;
    QPushButton* m_pNextButton = nullptr;
    CVolumeButton* m_pAudioButton = nullptr;

    QString m_playStyle;   // 播放按钮样式
    QString m_pauseStyle;  // 暂停按钮样式
    bool m_isPlaying;      // 当前播放状态
};


#endif // CPLAYBUTTONGROUPWIDGET_H
