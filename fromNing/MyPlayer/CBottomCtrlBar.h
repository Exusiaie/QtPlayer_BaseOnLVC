#ifndef CBOTTOMCTRLBAR_H
#define CBOTTOMCTRLBAR_H

#pragma once
#include "CPlayButtonGroupWidget.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
class CBottomCtrlBar : public QWidget
{
    Q_OBJECT
public:
    CBottomCtrlBar(QWidget* p = nullptr);
    ~CBottomCtrlBar();
    void showTimeLabel(bool isShow);
    void setCurPlayTime(const qint64& curMs);
    void setTotalTime(const qint64& totalMs);
private slots:
signals:
    void sig_play();    // play信号
    void sig_stop();
    void sig_fullScreen();
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
};


#endif // CBOTTOMCTRLBAR_H
