#include "widget.h"
#include "vlcwidget.h"
#include "qss.h"
#include "ctitlebar.h"
#include "cvolumedialog.h"
#include "cvolumebutton.h"

#include <string>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QLabel>
#include <QFrame>
#include <QMenu>

// 用于释放资源
#include <QTimer>
#include <QThread>

using std::string;

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

Widget::Widget(QWidget *parent)
    : CFramelessWidget(parent)
{
    initialize_basic_UI();
    initialize_central_button();
    initialize_control_panel();
    connect_UI_controls();
    connect_VLC_widget_signals();
    apply_styles();
}

Widget::~Widget()
{
    // 释放按钮资源
    if(m_open_button) { delete m_open_button; }
    if(m_play_button) { delete m_play_button; }
    if(m_pause_button) { delete m_pause_button; }
    if(m_stop_button) { delete m_stop_button; }
    if(m_title_bar)   { delete m_title_bar; }
    // 不需要手动删除m_volume_button，因为它有父部件
}

// 初始化UI元素和主布局
// - 设置窗口标题和尺寸，创建主布局，创建VLCWidget实例
// - 创建标题栏
// - 创建控制窗口
void Widget::initialize_basic_UI()
{
    // 1.设置窗体
    // - 名称与尺寸
    setWindowTitle("VLCWidget");
    resize(800, 700);

    // - 创建主布局
    m_main_layout = new QVBoxLayout(this);

    // 2.创建标题栏与窗口
    // - 创建标题栏（使用CTitleBar替代原来的自定义标题栏）
    //QWidget *title_bar = new QWidget(this);
    //title_bar->setFixedHeight(40);
    m_title_bar = new CTitleBar(this);

    // 3.创建VLCWidget实例， 解决use of undeclared vlcWidget错误
    m_vlc_widget = new VLCWidget(this);
    log_info("完成VLCWidget创建");

/*
    // - QWidget 本身不会自动排列子控件
    // - 必须通过布局（QHBoxLayout/QVBoxLayout 等）管理子控件的位置和大小
    // - 注释原因：交给ctitlebar.h处理
    QHBoxLayout *title_layout = new QHBoxLayout(m_title_bar);
    m_central_play_button = new QPushButton("菜单");
    m_central_play_button->setFixedWidth(80);
    title_layout->addWidget(m_central_play_button);
    title_layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 强制左对齐，垂直居中
*/

    // 4.创建控制窗口（播放区域）
    m_control_window = new QWidget(this);
    m_control_window->setStyleSheet("background-color: white;");
    m_vlc_widget->set_video_widget(m_control_window);
    log_info("完成m_vlc_widget创建");

    // 5.添加到主布局
    //m_main_layout->addLayout(m_title_bar->getHLayout());  // 会报错
    m_main_layout->addWidget(m_title_bar);
    m_main_layout->addWidget(m_control_window, 1);
    log_info("完成initialize_basic_UI;");
}

// 初始化菜单栏
// - 创建菜单
// - 设置菜单图标和快捷键
// - 创建菜单项
// - 连接菜单信号
void Widget::initialize_central_button()
{
    log_info("进入initialize_central_button();");

    // 1.创建中央播放按钮
    m_central_play_button = new QPushButton(m_control_window);

    // 设置最小和最大尺寸
    m_central_play_button->setMinimumSize(200, 60);  // 最小 200w x 60h
    m_central_play_button->setMaximumSize(400, 120); // 最大 400w x 120h

    // 设置按钮样式
    m_central_play_button->setStyleSheet(
        "QPushButton {border-radius: 10px; background-color: rgba(0, 0, 0, 0.5); padding: 5px;}"
        "QPushButton:hover {background-color: rgba(0, 0, 0, 0.7);}"
        "QPushButton:pressed {background-color: rgba(0, 0, 0, 0.3);}"
    );

    // 2.创建容器widget来放置三个内容元素
    QWidget *buttonContent = new QWidget(m_central_play_button);
    QHBoxLayout *contentLayout = new QHBoxLayout(buttonContent);
    contentLayout->setSpacing(5); // 设置间隔距离为5
    contentLayout->setContentsMargins(10, 5, 10, 5); // 设置内边距

    // 2.1 添加SVG图片
    QLabel *iconLabel = new QLabel(buttonContent);
    QPixmap pixmap(":/resources/file.png");
    // 确保图片是正方形的
    int iconSize = qMin(m_central_play_button->minimumHeight() - 10, 40); // 减去边距，最大40
    iconLabel->setPixmap(pixmap.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    contentLayout->addWidget(iconLabel, 0, Qt::AlignVCenter);

    // 2.2 添加垂直分隔符
    QFrame *line = new QFrame(buttonContent);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    contentLayout->addWidget(line);

    // 2.3 添加文字
    QLabel *textLabel = new QLabel("打开文件夹", buttonContent);
    textLabel->setStyleSheet("color: white; font-family: 'Microsoft YaHei'; font-size: 14px;");
    contentLayout->addWidget(textLabel, 0, Qt::AlignVCenter);

    // 3.设置按钮的布局
    QVBoxLayout *buttonLayout = new QVBoxLayout(m_central_play_button);
    buttonLayout->addWidget(buttonContent, 0, Qt::AlignCenter);

    // 4.创建布局使按钮居中
    QVBoxLayout *central_layout = new QVBoxLayout(m_control_window);
    central_layout->addWidget(m_central_play_button, 0, Qt::AlignCenter);

    log_info("完成initialize_central_button();");
}

// 初始化底部控制栏和相关控件
// - 创建底部栏
// - 创建播放控制按钮
// - 创建时间进度条和音量滑块
// - 设置底部布局
void Widget::initialize_control_panel()
{
    log_info("进入initialize_control_panel();");

    // 1.底部栏（限制高度，指定颜色）
    QWidget *buttom_bar = new QWidget(this);
    buttom_bar->setFixedHeight(60);

    // 2.创建播放控制按钮
    m_open_button = new QPushButton("打开视频");
    m_play_button = new QPushButton("播放");
    m_pause_button = new QPushButton("暂停");
    m_stop_button = new QPushButton("停止");

    // 3.创建时间进度条和时间显示
    m_time_slider = new QSlider(Qt::Horizontal);
    m_time_label = new QLabel("00:00:00/00:00:00");

/*  // - 创建音量滑块与音量显示
    // - m_volume_slider被m_volume_slider_dialog所替换
    // - m_volume_slider与m_volume_label托管到cvolumebutton处理
//    m_volume_slider = new QSlider(Qt::Horizontal);
//    m_volume_slider->setRange(0, 100);
//    m_volume_slider->setValue(20);                // 默认音量20%
//    m_volume_label = new QLabel("音量");


//    // - 初始化音量对话框
//    m_volume_slider_dialog = new CVolumeSliderDialog(this);
//    m_volume_slider_dialog->getSlider()->setRange(0, 100);
//    m_volume_slider_dialog->getSlider()->setValue(20);
//    m_volume_slider_dialog->hide();                 // 初始隐藏
*/
    m_volume_button = new CVolumeButton(this);

    // 4.设置底部按钮
    // - 底部按钮布局（保持距离，均分，留白）
    // - 上下两层，上层时间进度条，下层按钮与音量
    QVBoxLayout *bottomLayout = new QVBoxLayout(buttom_bar);
    // - 如果指定父部件，会引发报错：QLayout: Attempting to add QLayout to QWidget which already has a layout
    // - 错误原因是创建布局时多次指定了相同的父部件
    QHBoxLayout *firstLayer = new QHBoxLayout();    // 不指定父部件
    QHBoxLayout *secondLayer = new QHBoxLayout();
    //bottomLayout->setContentsMargins(10, 5, 10, 5);

    firstLayer->addWidget(m_time_slider, 1);        // 进度条拉伸

    secondLayer->addWidget(m_time_label);
    secondLayer->addWidget(m_volume_button);
    secondLayer->addStretch();                      // 按钮与进度条之间留白
    secondLayer->addWidget(m_open_button);
    secondLayer->addWidget(m_play_button);
    secondLayer->addWidget(m_pause_button);
    secondLayer->addWidget(m_stop_button);
//    secondLayer->addWidget(m_volume_slider);

    bottomLayout->addLayout(firstLayer);
    bottomLayout->addLayout(secondLayer);

    // 5.设置主布局
    m_main_layout->addWidget(buttom_bar);
    setLayout(m_main_layout);

    log_info("完成initialize_control_panel();");
}

// 连接UI控件信号与槽
// - 连接时间进度条信号
// - 连接音量滑块信号
// - 连接按钮信号
void Widget::connect_UI_controls()
{

    log_info("进入");

    // 第一类lambda函数：UI控件信号的响应函数:
    // - 用户交互触发，例如手动拖动时间滑块或者音量滑块会被调用

    // 1.连接时间进度条信号
    connect(m_time_slider, &QSlider::sliderMoved, this, [=](int value)
        {
            float pos = static_cast<float>(value) / 100.0f;                            // 计算百分比
            libvlc_media_player_set_position(m_vlc_widget->get_media_player(), pos);   // 显示位置
        }
    );

    // 2.连接音量滑动条信号
    // - 以下两个函数交给cvolumedialog.h 处理
//    connect(m_volume_slider, &QSlider::valueChanged, this, [=](int value)
//        {
//            libvlc_audio_set_volume(m_vlc_widget->get_media_player(), value);          // 显示位置
//            m_volume_label->setText(QString("音量: %1%").arg(value));
//        }
//    );

//    // - 修复对话框滑块信号连接
//    connect(m_volume_slider_dialog->getSlider(), &QSlider::valueChanged, this, [=](int value) {
//        libvlc_audio_set_volume(m_vlc_widget->get_media_player(), value);
//        m_volume_label->setText(QString("音量: %1%").arg(value));
//        log_info(QString("滑块值变化: %1").arg(value).toUtf8().data());
//    });

    // 连接滑块值变化信号
    // - 同样以代理的思路去调整

    // - 注意，这一步实现的前提，是将成员函数_pslider与CVolumeSliderDialog关联，否则就是无效的，自定义信号系统检测不到变化
//    connect(m_volume_button->getVolumeSliderDialog(), &CVolumeSliderDialog::valueChanged, this, [=](int value)
    connect(m_volume_button->getVolumeSliderDialog()->getSlider(), &QSlider::valueChanged, this, [=](int value)
        {
            int validValue = qBound(0, value, 100); // 过滤无效值（确保在0-100之间）,小于0取0，大于100取100
            log_info(QString("connect响应，音量按钮信号: %1").arg(validValue).toUtf8().data());
            // 直接调用VLC API设置音量
            libvlc_audio_set_volume(m_vlc_widget->get_media_player(), validValue);
            m_volume_button->setVolumeValue(validValue);
            m_volume_button->setVolumeLabel(QString("音量: %1%").arg(validValue));
//            _volumeValue = value;
//            _volumeLabel->setText(QString("音量: %1%").arg(value));
//            emit m_volume_button->volumeChanged(value);
        }
    );

//    // 直接连接音量按钮信号到VLC音量控制
//    connect(m_volume_button, &CVolumeButton::volumeChanged, this, [=](int value)
//        {
//            log_info(QString("connect响应，音量按钮信号: %1").arg(value).toUtf8().data());
//            // 直接调用VLC API设置音量
//            libvlc_audio_set_volume(m_vlc_widget->get_media_player(), value);
//            // 同时更新UI滑块值
//            // - 写了也白写啊，vlc代理了一圈信号，最后widget的处理被注释了
//            //emit m_vlc_widget->set_volume_slider_value(value);
//            m_volume_button->setVolumeValue(value);
//            m_volume_button->setVolumeLabel(QString("音量: %1%").arg(value));
//        }
//    );

    // 3.连接按钮信号
    // - 播放界面按钮
    connect(m_central_play_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_openbtn_clicked);
    connect(m_vlc_widget, &VLCWidget::hide_central_button, this, &Widget::on_hide_central_button);

    // - 底部控制栏按钮
    connect(m_open_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_openbtn_clicked);
    connect(m_play_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_playbtn_clicked);
    connect(m_pause_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_pausebtn_clicked);
    connect(m_stop_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_stopbtn_clicked);
    connect(m_title_bar, &CTitleBar::sigClose, this, &Widget::on_title_bar_close);

//    // 添加音量按钮信号连接
//    connect(m_volume_button, &CVolumeButton::volumeChanged, this, [=](int value) {
//        log_info(QString("音量按钮信号: %1").arg(value).toUtf8().data());
//        libvlc_audio_set_volume(m_vlc_widget->get_media_player(), value);
////        m_volume_label->setText(QString("音量: %1%").arg(value));
//    });

    // 确保对话框在主窗口上方
    connect(m_volume_button, &CVolumeButton::clicked, this, [=]()
    {
        m_volume_button->getVolumeSliderDialog()->show();
        m_volume_button->getVolumeSliderDialog()->raise();
    });

    log_info("完成");
}

// 连接VLCWidget信号与UI更新槽
// - 连接播放进度更新信号
// - 连接时间显示更新信号
// - 连接音量更新信号
void Widget::connect_VLC_widget_signals()
{
    log_info("进入");

    // 第二类lambda函数：VLCWidget信号的响应函数，连接VLCWidget的信号到Widget的槽
    // - 由播放器内部状态变化触发，当VLC播放器改变时由VLCWidget发出信号触发，例如播放进度，音量改变时
    // - 注意第2个参数是信号，不要稀里糊涂地写为槽函数

    // 1.连接播放进度更新信号
    connect(m_vlc_widget, &VLCWidget::set_timer_slider_value, this, [=](int value)
        {
            m_time_slider->setValue(value);
        }
    );

    // 2.连接时间显示更新信号
    connect(m_vlc_widget, &VLCWidget::set_timer_text, this, [=](const QString &text)
        {
            m_time_label->setText(text);
        }
    );

    // 3.连接音量更新信号
    // - 注释掉看一下能不能跑，如果不能跑，直接代理到下层就行了
//    connect(m_volume_button, &CVolumeButton::volumeChanged, this, [=](int value)
//        {
//            m_vlc_widget->set_volume_slider_value(value);
//        }
//    );

    // - vlc要用，还是别注释了
    connect(m_vlc_widget, &VLCWidget::set_volume_slider_value, this, [=](int value)
        {
            log_info(QString("connect响应，音量按钮信号: %1").arg(value).toUtf8().data());
            m_volume_button->setVolumeValue(value);
            m_volume_button->setVolumeLabel(QString("%1%").arg(value));
        }
    );

    log_info("完成");
}

// 应用样式表
// - 设置各种UI元素的样式
void Widget::apply_styles()
{
    log_info("进入");

    this->setStyleSheet(QString::fromStdString(button_qss));
    this->setStyleSheet(QString::fromStdString(logo_button_qss));
    this->setStyleSheet(QString::fromStdString(menu_qss));
    this->setStyleSheet(QString::fromStdString(minimode_qss));
    this->setStyleSheet(QString::fromStdString(settop_qss));
    this->setStyleSheet(QString::fromStdString(min_qss));
    this->setStyleSheet(QString::fromStdString(max_qss));
    this->setStyleSheet(QString::fromStdString(close_qss));

    log_info("完成");
}

void Widget::on_title_bar_close()
{
    log_info("进入on_title_bar_close()");

    // 1. 先停止播放（关键：避免vlc资源占用导致的强制退出）
    if(m_vlc_widget)
    {
        // 1.先停止所有播放操作
        if (m_vlc_widget->get_media_list_player())
        {
            libvlc_media_list_player_stop(m_vlc_widget->get_media_list_player());
            log_info("m_media_list_player已释放");
        }

        if (m_vlc_widget->get_media_player())
        {
            libvlc_media_player_stop(m_vlc_widget->get_media_player());
            log_info("m_media_player已释放");
        }

        log_info("已停止所有播放");
    }

    // 2. 延迟释放资源（给vlc足够时间清理，避免异步操作冲突）
    QTimer::singleShot(500, this, [=]() {
        // 3. 安全释放资源并关闭窗口
        log_info("m_vlc_widget预备释放");
        if (m_vlc_widget) {
            delete m_vlc_widget;
            m_vlc_widget = nullptr; // 避免重复释放
            log_info("m_vlc_widget已释放");
        }

        log_info("完成on_title_bar_close()");
        close(); // 最后关闭窗口
    });
}

void Widget::on_hide_central_button()
{
    if (m_central_play_button)
    {
        m_central_play_button->hide();
        log_info("中央播放按钮已隐藏");
    }
}
