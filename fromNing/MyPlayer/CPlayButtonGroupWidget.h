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
signals:
void sig_play();
void sig_stop();
void sig_next();
void sig_pre();
private:
QPushButton* m_pStopButton = nullptr;
QPushButton* m_pPreButton = nullptr;
QPushButton* m_pPlayButton = nullptr;
QPushButton* m_pNextButton = nullptr;
CVolumeButton* m_pAudioButton = nullptr;
};


#endif // CPLAYBUTTONGROUPWIDGET_H
