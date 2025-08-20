#include "CPlayButtonGroupWidget.h"
#include <QHBoxLayout>
CPlayButtonGroupWidget::CPlayButtonGroupWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground); // 禁止父窗口样式影响子控件样式
    m_pStopButton = new QPushButton(this);
    m_pStopButton->setText("");
    m_pStopButton->setFixedSize(32, 32);
    m_pStopButton->setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/stop.svg);border:none;}"
                                 "QPushButton:hover{background-image:url(:/Resource/playctrlBar/stop_hover.svg);border:none;}"
                                 "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/stop.svg);border:none;}");
    m_pPreButton = new QPushButton(this);
    m_pPreButton->setText("");
    m_pPreButton->setFixedSize(32, 32);
    m_pPreButton->setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/pre.svg);border:none;}"
                                "QPushButton:hover{background-image:url(:/Resource/playctrlBar/pre_hover.svg);border:none;}"
                                "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/pre.svg);border:none;}");
    m_pPlayButton = new QPushButton(this);
    m_pPlayButton->setText("");
    m_pPlayButton->setFixedSize(48, 48);
    // 保存两种样式
    m_playStyle = "QPushButton{background-image:url(:/Resource/playctrlBar/play.svg);border:none;}"
                  "QPushButton:hover{background-image:url(:/Resource/playctrlBar/play_hover.svg);border:none;}"
                  "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/play.svg);border:none;}";
    m_pauseStyle = "QPushButton{background-image:url(:/Resource/playctrlBar/pause.svg);border:none;}"
                   "QPushButton:hover{background-image:url(:/Resource/playctrlBar/pause_hover.svg);border:none;}"
                   "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/pause.svg);border:none;}";
    m_pPlayButton->setStyleSheet(m_playStyle); // 初始为播放样式

    m_pNextButton = new QPushButton(this);
    m_pNextButton->setText("");
    m_pNextButton->setFixedSize(32, 32);
    m_pNextButton->setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/next.svg);border:none;}"
                                 "QPushButton:hover{background-image:url(:/Resource/playctrlBar/next_hover.svg);border:none;}"
                                 "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/next.svg);border:none;}");
    m_pAudioButton = new CVolumeButton(this);
    m_pAudioButton->setText("");
    m_pAudioButton->setFixedSize(32, 32);
    QHBoxLayout* pHLay = new QHBoxLayout(this);
    pHLay->addWidget(m_pStopButton);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pPreButton);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pPlayButton);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pNextButton);
    pHLay->setSpacing(8);
    pHLay->addWidget(m_pAudioButton);
    pHLay->setContentsMargins(0, 0, 0, 0);
    setLayout(pHLay);
    setFixedSize(32 * 4 + 48 + 4 * 8 + 20 , 48);
    connect(m_pPlayButton, &QPushButton::clicked, this,     // 信号转发: 控件本身并不处理按钮的点击事件，而是将这些内部按钮发出的信号再次作为自己的信号向外发射。
            &CPlayButtonGroupWidget::sig_play);
    connect(m_pStopButton, &QPushButton::clicked, this,
            &CPlayButtonGroupWidget::sig_stop);
    connect(m_pPreButton, &QPushButton::clicked, this,
            &CPlayButtonGroupWidget::sig_pre);
    connect(m_pNextButton, &QPushButton::clicked, this,
            &CPlayButtonGroupWidget::sig_next);
    connect(m_pAudioButton, &CVolumeButton::sliderValueChanged, this, &CPlayButtonGroupWidget::sliderValueChanged);
}

void CPlayButtonGroupWidget::setPlaying(bool playing)
{
    m_isPlaying = playing;
    if (m_isPlaying) {
        m_pPlayButton->setStyleSheet(m_pauseStyle);
    } else {
        m_pPlayButton->setStyleSheet(m_playStyle);
    }
}

CPlayButtonGroupWidget::~CPlayButtonGroupWidget()
{
}
