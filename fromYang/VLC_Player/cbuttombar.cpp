// ... existing code ...
#include "cbuttombar.h"
#include "cvolumebutton.h"
#include "qss.h"

// 日志宏定义
#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);

CButtomBar::CButtomBar(QWidget *parent) : QWidget(parent)
{
    // 1.设置底部栏高度
    setFixedHeight(60);

    // 2.创建播放控制按钮
    m_open_button = new QPushButton("打开视频");
    m_play_button = new QPushButton("播放");
    m_pause_button = new QPushButton("暂停");
    m_stop_button = new QPushButton("停止");

    // 3.创建时间进度条和时间显示
    m_time_slider = new QSlider(Qt::Horizontal);
    m_time_slider->setStyleSheet(QString::fromStdString(slider_qss));
    m_time_label = new QLabel("00:00:00/00:00:00");
    m_time_label->setStyleSheet(QString::fromStdString(time_label_qss));

    // 4.创建音量按钮
    m_volume_button = new CVolumeButton(this);

    // 5.设置底部按钮布局
    // - 上下两层，上层时间进度条，下层按钮与音量
    QVBoxLayout *bottomLayout = new QVBoxLayout(this);
    QHBoxLayout *firstLayer = new QHBoxLayout();
    QHBoxLayout *secondLayer = new QHBoxLayout();

    firstLayer->addWidget(m_time_slider, 1);  // 进度条拉伸

    secondLayer->addWidget(m_time_label);
    secondLayer->addWidget(m_volume_button);
    secondLayer->addStretch();                // 按钮与进度条之间留白
    secondLayer->addWidget(m_open_button);
    secondLayer->addWidget(m_play_button);
    secondLayer->addWidget(m_pause_button);
    secondLayer->addWidget(m_stop_button);

    bottomLayout->addLayout(firstLayer);
    bottomLayout->addLayout(secondLayer);

    // 6.连接信号
    connect(m_open_button, &QPushButton::clicked, this, &CButtomBar::onOpenButtonClicked);
    connect(m_play_button, &QPushButton::clicked, this, &CButtomBar::onPlayButtonClicked);
    connect(m_pause_button, &QPushButton::clicked, this, &CButtomBar::onPauseButtonClicked);
    connect(m_stop_button, &QPushButton::clicked, this, &CButtomBar::onStopButtonClicked);
    connect(m_time_slider, &QSlider::sliderMoved, this, &CButtomBar::onTimeSliderMoved);

    log_info("完成CButtomBar初始化");
}

// 访问控件的方法实现
QPushButton* CButtomBar::getOpenButton() const { return m_open_button; }
QPushButton* CButtomBar::getPlayButton() const { return m_play_button; }
QPushButton* CButtomBar::getPauseButton() const { return m_pause_button; }
QPushButton* CButtomBar::getStopButton() const { return m_stop_button; }
QSlider* CButtomBar::getTimeSlider() const { return m_time_slider; }
QLabel* CButtomBar::getTimeLabel() const { return m_time_label; }
CVolumeButton* CButtomBar::getVolumeButton() const { return m_volume_button; }

// 信号处理槽实现
void CButtomBar::onOpenButtonClicked() { emit openButtonClicked(); }
void CButtomBar::onPlayButtonClicked() { emit playButtonClicked(); }
void CButtomBar::onPauseButtonClicked() { emit pauseButtonClicked(); }
void CButtomBar::onStopButtonClicked() { emit stopButtonClicked(); }
void CButtomBar::onTimeSliderMoved(int value) { emit timeSliderMoved(value); }
