#include "CBottomCtrlBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

CBottomCtrlBar::CBottomCtrlBar(QWidget* p)
    : QWidget(p)
{
    // 禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);
    this->setFixedHeight(80);
    setStyleSheet("background-color:rgb(67,67,67)");

    // ---------------------- 组件创建 ----------------------
    // 时间标签
    QString label_qss = "QLabel{font-family:Microsoft YaHei; font-size:18px;color:rgb(255,255,255);}";
    m_pCurPlayTimeLabel = new QLabel(this);
    m_pCurPlayTimeLabel->setText("00:00:00");
    m_pCurPlayTimeLabel->setAlignment(Qt::AlignRight);
    m_pCurPlayTimeLabel->setFixedSize(80, 32);
    m_pCurPlayTimeLabel->setStyleSheet(label_qss);

    m_pTotalTimeLabel = new QLabel(this);
    m_pTotalTimeLabel->setText("00:00:00");
    m_pTotalTimeLabel->setAlignment(Qt::AlignLeft);
    m_pTotalTimeLabel->setFixedSize(160, 32);
    m_pTotalTimeLabel->setStyleSheet(label_qss);

    // 按钮
    m_pPlayButtonGroupWidget = new CPlayButtonGroupWidget(this);
    m_pToolBoxButton = new QPushButton(this);
    m_pToolBoxButton->setText("");
    m_pToolBoxButton->setFixedSize(32, 32);
    m_pToolBoxButton->setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/toolbox_hover.svg);border:none;}"
                                    "QPushButton:hover{background-image:url(:/Resource/playctrlBar/toolbox.svg);border:none;}"
                                    "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/toolbox.svg);border:none;}");

    m_pEffectButton = new QPushButton(this);
    m_pEffectButton->setText("");
    m_pEffectButton->setFixedSize(32, 32);
    m_pEffectButton->setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/effect.svg);border:none;}"
                                   "QPushButton:hover{background-image:url(:/Resource/playctrlBar/effect_hover.svg);border:none;}"
                                   "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/effect.svg);border:none;}");

    m_pFullscreenButton = new QPushButton(this);
    m_pFullscreenButton->setText("");
    m_pFullscreenButton->setFixedSize(32, 32);
    m_pFullscreenButton->setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/fullscreen.svg);border:none;}"
                                       "QPushButton:hover{background-image:url(:/Resource/playctrlBar/fullscreen_hover.svg);border:none;}"
                                       "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/fullscreen.svg);border:none;}");

    // 进度条
    m_pProgressSlider = new QSlider(Qt::Horizontal, this);
    m_pProgressSlider->setRange(0, 100);
    m_pProgressSlider->setSingleStep(1);
    m_pProgressSlider->setPageStep(5);

    // ---------------------- 布局管理 ----------------------
    // 1. 创建主垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // 顶部边距设为0以消除空隙
    mainLayout->setContentsMargins(10, 0, 10, 5);
    mainLayout->setSpacing(5);

    // 2. 创建用于放置进度条的水平布局
    QHBoxLayout *progressLayout = new QHBoxLayout();
    progressLayout->addWidget(m_pProgressSlider);

    // 3. 创建一个子水平布局，专门用于左侧的时间标签
    QHBoxLayout *timeLabelsLayout = new QHBoxLayout();
    timeLabelsLayout->addWidget(m_pCurPlayTimeLabel);
    timeLabelsLayout->addSpacing(1);
    timeLabelsLayout->addWidget(m_pTotalTimeLabel);

    // 4. 创建一个子水平布局，专门用于右侧的工具按钮
    QHBoxLayout *toolButtonsLayout = new QHBoxLayout();
    toolButtonsLayout->addWidget(m_pToolBoxButton);
    toolButtonsLayout->addSpacing(18);
    toolButtonsLayout->addWidget(m_pEffectButton);
    toolButtonsLayout->addSpacing(18);
    toolButtonsLayout->addWidget(m_pFullscreenButton);

    // 5. 创建主控制条的水平布局
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(0);

    // -------- 左侧区域：时间标签 --------
    QWidget *leftArea = new QWidget(this);
    leftArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    auto *leftLay = new QHBoxLayout(leftArea);
    leftLay->setContentsMargins(0, 0, 0, 0);
    leftLay->setSpacing(1);
    leftLay->addWidget(m_pCurPlayTimeLabel);
    leftLay->addWidget(m_pTotalTimeLabel);
    leftLay->addStretch();  // 让标签贴左边

    // -------- 中间区域：播放按钮组 --------
    m_pPlayButtonGroupWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QWidget *centerArea = new QWidget(this);
    auto *centerLay = new QHBoxLayout(centerArea);
    centerLay->setContentsMargins(0, 0, 0, 0);
    centerLay->setSpacing(0);
    centerLay->addStretch();
    centerLay->addWidget(m_pPlayButtonGroupWidget, 0, Qt::AlignCenter);
    centerLay->addStretch();

    // -------- 右侧区域：工具按钮（靠右） --------
    QWidget *rightArea = new QWidget(this);
    rightArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    auto *rightLay = new QHBoxLayout(rightArea);
    rightLay->setContentsMargins(0, 0, 0, 0);
    rightLay->setSpacing(18);
    rightLay->addStretch();  // 让按钮贴右边
    rightLay->addWidget(m_pToolBoxButton);
    rightLay->addSpacing(18);
    rightLay->addWidget(m_pEffectButton);
    rightLay->addSpacing(18);
    rightLay->addWidget(m_pFullscreenButton);

    // -------- 组装三块区域，并设置拉伸因子 1:0:1 --------
    controlsLayout->addWidget(leftArea);
    controlsLayout->addWidget(centerArea);
    controlsLayout->addWidget(rightArea);
    controlsLayout->setStretch(0, 1);  // 左侧区域占“可扩展”空间
    controlsLayout->setStretch(1, 0);  // 中间区域仅按自身大小
    controlsLayout->setStretch(2, 1);  // 右侧区域占“可扩展”空间

    // 将所有子布局添加到主垂直布局中
    mainLayout->addLayout(progressLayout);
    mainLayout->addLayout(controlsLayout);



    // ---------------------- 信号连接 ----------------------
    showTimeLabel(false); // 初始隐藏时间标签

    // 转发 CPlayButtonGroupWidget 的信号
    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_play,
            this, &CBottomCtrlBar::sig_play);
    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_stop,
            this, &CBottomCtrlBar::sig_stop);
    connect(m_pFullscreenButton, &QPushButton::clicked,
            this, &CBottomCtrlBar::sig_fullScreen);
    connect(m_pToolBoxButton, &QPushButton::clicked,
            this, &CBottomCtrlBar::sig_open);

    // 推荐：用户“松手”后再进行 seek，避免频繁跳转
    connect(m_pProgressSlider, &QSlider::sliderMoved, this, [this]{
        emit sig_seek(m_pProgressSlider->value());
    });

    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sliderValueChanged, this, &CBottomCtrlBar::sliderValueChanged);

}

CBottomCtrlBar::~CBottomCtrlBar()
{
}

void CBottomCtrlBar::showTimeLabel(bool isShow)
{
    if (isShow)
    {
        m_pCurPlayTimeLabel->show();
        m_pTotalTimeLabel->show();
    }
    else
    {
        m_pCurPlayTimeLabel->hide();
        m_pTotalTimeLabel->hide();
    }
}

void CBottomCtrlBar::setPlaying(bool playing)
{
    if (m_pPlayButtonGroupWidget) {
        m_pPlayButtonGroupWidget->setPlaying(playing);
        showTimeLabel(true);
    }
}

QString CBottomCtrlBar::formatTimeMs(const qint64& timeMs)
{
    qDebug() << "更新时间函数";
    qint64 seconds = timeMs / 1000;
    int hours = seconds / 3600;
    int mins = (seconds - hours * 3600) / 60;
    int secs = seconds - hours * 3600 - mins * 60;
    char buf[1024] = { 0 };
    if (hours < 100)
    {
        sprintf(buf, "%02d:%02d:%02d", hours, mins, secs);
    }
    else
    {
        sprintf(buf, "%d:%02d:%02d", hours, mins, secs);
    }
    return QString::fromUtf8(buf);
}

void CBottomCtrlBar::setCurPlayTime(const qint64& curMs)
{
    qDebug() << "调用更新时间函数";
    m_pCurPlayTimeLabel->setText(formatTimeMs(curMs));
}

void CBottomCtrlBar::setTotalTime(const qint64& totalMs)
{
    m_pTotalTimeLabel->setText("/" + formatTimeMs(totalMs));
}

void CBottomCtrlBar::resizeEvent(QResizeEvent* event)
{
    // 使用布局管理器后，通常不再需要手动调整子部件尺寸
    QWidget::resizeEvent(event);
}

void CBottomCtrlBar::setPositionByPercent(int positionPercent)
{
    if (!m_pProgressSlider) return;
    const QSignalBlocker blocker(m_pProgressSlider);
    if (positionPercent < 0) positionPercent = 0;
    if (positionPercent > 100) positionPercent = 100;
    m_pProgressSlider->setValue(positionPercent);
}

void CBottomCtrlBar::onTimeChanged(qint64 current, qint64 total)
{


    // 将毫秒转换为 HH:MM:SS 格式
    QString currentStr = QString("%1:%2:%3")
        .arg(current / 3600000, 2, 10, QChar('0'))
        .arg((current / 60000) % 60, 2, 10, QChar('0'))
        .arg((current / 1000) % 60, 2, 10, QChar('0'));

    QString totalStr = QString("%1:%2:%3")
        .arg(total / 3600000, 2, 10, QChar('0'))
        .arg((total / 60000) % 60, 2, 10, QChar('0'))
        .arg((total / 1000) % 60, 2, 10, QChar('0'));

     m_pCurPlayTimeLabel->setText(QString("%1").arg(currentStr));
     m_pTotalTimeLabel->setText(QString("/ %1").arg(totalStr));
}
