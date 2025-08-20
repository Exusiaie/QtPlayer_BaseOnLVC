#ifndef CBOTTOMCTRLBAR_H
#define CBOTTOMCTRLBAR_H

#pragma once
#include "CPlayButtonGroupWidget.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
class CBottomCtrlBar : public QWidget
{
    Q_OBJECT
public:
    CBottomCtrlBar(QWidget* p = nullptr);
    ~CBottomCtrlBar();
    void showTimeLabel(bool isShow);
    void setPlaying(bool playing);
    void setCurPlayTime(const qint64& curMs);
    void setTotalTime(const qint64& totalMs);
public slots:
    void setPositionByPercent(int positionPercent);  // 外部（比如 VLCKits 的信号）来更新当前播放位置百分比// -----------------进度条功能
    void onTimeChanged(qint64 current, qint64 total); // 用来接收VLCKits 发出的 sigTimeChanged 信号
signals:
    void sig_play();    // play信号
    void sig_stop();
    void sig_fullScreen();

    void sig_seek(int positionPercent); // 用户拖动并松手时，告诉外部要跳转到百分比 position (0~100)// -----------------进度条功能
    void sliderValueChanged(int value);
    void sig_open();

private:
    QString formatTimeMs(const qint64& timeMs);
private:
    void resizeEvent(QResizeEvent* event) override;
private:
    QLabel* m_pCurPlayTimeLabel = nullptr;
    QLabel* m_pTotalTimeLabel = nullptr;
    CPlayButtonGroupWidget* m_pPlayButtonGroupWidget = nullptr;
    QPushButton* m_pToolBoxButton = nullptr;
    QPushButton* m_pEffectButton = nullptr;
    QPushButton* m_pFullscreenButton = nullptr;

    QSlider *m_pProgressSlider = nullptr;                        // -----------------进度条功能
};


#endif // CBOTTOMCTRLBAR_H
