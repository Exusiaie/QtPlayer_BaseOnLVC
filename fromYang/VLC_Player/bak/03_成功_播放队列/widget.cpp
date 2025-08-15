#include "vlcwidget.h"
#include "widget.h"
#include "ui_widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QFrame>

class VLCWidget;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 创建VLCWidget实例， 解决use of undeclared vlcWidget错误
    VLCWidget *vlcWidget = new VLCWidget(this);

    // 1.设置窗体
    // - 名称与尺寸
    setWindowTitle("VLCWidget");
    resize(800, 700);

    // - 创建主布局
    m_main_layout = new QVBoxLayout(this);

    // 2.标题栏
    // - 外部布局
    QWidget *title_bar = new QWidget(this);
    title_bar->setFixedHeight(40);
    title_bar->setStyleSheet("background-color:#333333;");

    // 3. 控制窗口（播放区域）
    QWidget *control_window = new QWidget(this);
    vlcWidget->set_video_widget(control_window);

    // 4. 底部栏（限制高度，指定颜色）
    QWidget *buttom_bar = new QWidget(this);
    buttom_bar->setFixedHeight(60);
    buttom_bar->setStyleSheet("background-color:#f0f0f0;");

    // - 创建控制按钮
    m_open_button = new QPushButton("打开视频");
    m_play_button = new QPushButton("播放");
    m_pause_button = new QPushButton("暂停");
    m_stop_button = new QPushButton("停止");

    // - 连接按钮信号
    connect(m_open_button, &QPushButton::clicked, vlcWidget, &VLCWidget::on_openbtn_clicked);
    connect(m_play_button, &QPushButton::clicked, vlcWidget, &VLCWidget::on_playbtn_clicked);
    connect(m_pause_button, &QPushButton::clicked, vlcWidget, &VLCWidget::on_pausebtn_clicked);
    connect(m_stop_button, &QPushButton::clicked, vlcWidget, &VLCWidget::on_stopbtn_clicked);

    // - 创建时间进度条和时间显示
    m_time_slider = new QSlider(Qt::Horizontal);
    m_time_label = new QLabel("00:00:00/00:00:00");

    // - 创建音量滑块与音量显示
    m_volume_slider = new QSlider(Qt::Horizontal);
    m_volume_slider->setRange(0, 100);
    m_volume_slider->setValue(20);      // 默认音量20%
    m_volume_label = new QLabel("音量");

    // 第一类lambda函数：UI控件信号的响应函数
    // - 用户交互触发，例如手动拖动时间滑块或者音量滑块会被调用
    // - 连接时间进度条信号
    connect(m_time_slider, &QSlider::sliderMoved, this, [=](int value)
        {
            float pos = static_cast<float>(value) / 100.0f;                         // 计算百分比
            libvlc_media_player_set_position(vlcWidget->get_media_player(), pos);   // 显示位置
        }
    );
    // - 连接音量滑动条信号
    connect(m_volume_slider, &QSlider::valueChanged, this, [=](int value)
        {
            libvlc_audio_set_volume(vlcWidget->get_media_player(), value);          // 显示位置
            m_volume_label->setText(QString("音量: %1%").arg(value));
        }
    );

    // 第二类lambda函数：VLCWidget信号的响应函数，连接VLCWidget的信号到Widget的槽
    // - 由播放器内部状态变化触发，当VLC播放器改变时由VLCWidget发出信号触发，例如播放进度，音量改变时
    // - 注意第2个参数是信号，不要稀里糊涂地写为槽函数
    connect(vlcWidget, &VLCWidget::set_timer_slider_value, this, [=](int value) {
        m_time_slider->setValue(value);
    });

    connect(vlcWidget, &VLCWidget::set_timer_text, this, [=](const QString &text) {
        m_time_label->setText(text);
    });

    connect(vlcWidget, &VLCWidget::set_volume_slider_value, this, [=](int value) {
        m_volume_slider->setValue(value);
        m_volume_label->setText(QString("音量: %1%").arg(value));
    });

    // - 底部按钮布局（保持距离，均分，留白）
    // - 上下两层，上层时间进度条，下层按钮与音量
    QVBoxLayout *bottomLayout = new QVBoxLayout(buttom_bar);
    // - 如果指定父部件，会引发报错：QLayout: Attempting to add QLayout to QWidget which already has a layout
    // - 错误原因是创建布局时多次指定了相同的父部件
    QHBoxLayout *firstLayer = new QHBoxLayout();    // 不指定父部件
    QHBoxLayout *secondLayer = new QHBoxLayout();
    bottomLayout->setContentsMargins(10, 5, 10, 5);

    firstLayer->addWidget(m_time_slider, 1);      // 进度条拉伸

    secondLayer->addWidget(m_time_label);
    secondLayer->addStretch();                   // 按钮与进度条之间留白
    secondLayer->addWidget(m_open_button);
    secondLayer->addWidget(m_play_button);
    secondLayer->addWidget(m_pause_button);
    secondLayer->addWidget(m_stop_button);
    secondLayer->addWidget(m_volume_label);
    secondLayer->addWidget(m_volume_slider);

    bottomLayout->addLayout(firstLayer);
    bottomLayout->addLayout(secondLayer);

    // 6. 设置主布局
    m_main_layout->addWidget(title_bar);
    m_main_layout->addWidget(control_window, 1);     //第2个参数表示拉伸因子
//    m_main_layout->addWidget(control_window);
    m_main_layout->addWidget(buttom_bar);
    setLayout(m_main_layout);

}

Widget::~Widget()
{
    // 释放按钮资源
    delete m_open_button;
    delete m_play_button;
    delete m_pause_button;
    delete m_stop_button;
}

