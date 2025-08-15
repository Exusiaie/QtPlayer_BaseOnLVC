#include "widget.h"
#include "vlcwidget.h"
#include "qss.h"
#include "ctitlebar.h"
#include "cplayzone.h"
#include "cbuttombar.h"
#include "cplaytaskqueue.h"
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
    initialize_play_task_queue();  // 初始化任务队列

    connect_UI_controls();
    connect_VLC_widget_signals();
    connect_play_task_queue_signals();  // 连接任务队列信号

    apply_styles();

    //    initialize_central_button();
    //    initialize_control_panel();
}

Widget::~Widget()
{
    // 释放按钮资源
    if(m_title_bar)   { delete m_title_bar; }
    if(m_play_zone)   { delete m_play_zone; }
    if(m_buttom_bar)  { delete m_buttom_bar; }
    if(m_play_task_queue) { delete m_play_task_queue; }

    // - 不需要手动删除m_volume_button，因为它有父部件
//    if(m_open_button) { delete m_open_button; }
//    if(m_play_button) { delete m_play_button; }
//    if(m_pause_button) { delete m_pause_button; }
//    if(m_stop_button) { delete m_stop_button; }
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
    m_main_layout->setSizeConstraint(QLayout::SetMinAndMaxSize); // 设置布局约束

    // 2.创建VLCWidget实例， 解决use of undeclared vlcWidget错误
    m_vlc_widget = new VLCWidget(this);
    log_info("完成VLCWidget创建");

    // 3.创建标题栏与窗口
    // - 创建标题栏（使用CTitleBar替代原来的自定义标题栏）
    m_title_bar = new CTitleBar(this);

    // 4.创建播放区域
    m_play_zone = new CPlayZone(this);
    m_vlc_widget->set_video_widget(m_play_zone);
    log_info("完成m_play_zone创建");

    // 5.创建底部控制栏
    m_buttom_bar = new CButtomBar(this);
    log_info("完成m_buttom_bar创建");

    // 6.创建播放区域容器
    QWidget *playAreaWidget = new QWidget(this);
    QVBoxLayout *playAreaLayout = new QVBoxLayout(playAreaWidget);
    playAreaLayout->addWidget(m_title_bar);
    playAreaLayout->addWidget(m_play_zone, 1);
    playAreaLayout->addWidget(m_buttom_bar);
    playAreaLayout->setContentsMargins(0, 0, 0, 0);

    // 7.创建水平布局，放置播放区域和任务队列
    QHBoxLayout *centralLayout = new QHBoxLayout();
    centralLayout->addWidget(playAreaWidget, 1); // 播放区域占主要空间

    // 8.添加到主布局
    //m_main_layout->addLayout(m_title_bar->getHLayout());  // 会报错
    m_main_layout->addLayout(centralLayout);
    log_info("完成initialize_basic_UI;");

}

// 新增初始化任务队列方法
void Widget::initialize_play_task_queue()
{
    m_play_task_queue = new CPlayTaskQueue(this);
    m_play_task_queue->hide();  // 初始隐藏

    // 将任务队列添加到布局
    QHBoxLayout *centralLayout = qobject_cast<QHBoxLayout*>(m_main_layout->itemAt(0)->layout());
    if (centralLayout)
    {
        centralLayout->addWidget(m_play_task_queue);
    }

    log_info("播放任务队列初始化完成");
}

/* // 初始化菜单栏
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
*/

/* // 初始化底部控制栏和相关控件
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

    // - 创建音量滑块与音量显示
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
*/

// 连接UI控件信号与槽
// - 连接时间进度条信号
// - 连接音量滑块信号
// - 连接按钮信号
void Widget::connect_UI_controls()
{

    log_info("进入connect_UI_controls()");

    // 第一类lambda函数：UI控件信号的响应函数:
    // - 用户交互触发，例如手动拖动时间滑块或者音量滑块会被调用

    // 1.连接时间进度条信号
    connect(m_buttom_bar, &CButtomBar::timeSliderMoved, this, [=](int value)
        {
            float pos = static_cast<float>(value) / 100.0f;
            libvlc_media_player_set_position(m_vlc_widget->get_media_player(), pos);
        }
    );

    // 2.连接音量滑动条信号
    // - 注意，这一步实现的前提，是将成员函数_pslider与CVolumeSliderDialog关联，否则就是无效的，自定义信号系统检测不到变化
    connect(m_buttom_bar->getVolumeButton()->getVolumeSliderDialog()->getSlider(), &QSlider::valueChanged, this, [=](int value)
        {
            int valid_value = qBound(0, value, 100);
            log_info(QString("connect响应，音量按钮信号: %1").arg(valid_value).toUtf8().data());
            libvlc_audio_set_volume(m_vlc_widget->get_media_player(), valid_value);
            m_buttom_bar->getVolumeButton()->setVolumeValue(valid_value);
            m_buttom_bar->getVolumeButton()->setVolumeLabel(QString("音量: %1%").arg(valid_value));
        }
    );

    // 3.连接按钮信号
    // - 播放界面按钮
    connect(m_play_zone, &CPlayZone::centralButtonClicked, m_vlc_widget, &VLCWidget::on_openbtn_clicked);
    connect(m_vlc_widget, &VLCWidget::hide_central_button, this, &Widget::on_hide_central_button);

    // - 底部控制栏按钮
    connect(m_buttom_bar, &CButtomBar::openButtonClicked, m_vlc_widget, &VLCWidget::on_openbtn_clicked);
    connect(m_buttom_bar, &CButtomBar::playButtonClicked, m_vlc_widget, &VLCWidget::on_playbtn_clicked);
    connect(m_buttom_bar, &CButtomBar::pauseButtonClicked, m_vlc_widget, &VLCWidget::on_pausebtn_clicked);
    connect(m_buttom_bar, &CButtomBar::stopButtonClicked, m_vlc_widget, &VLCWidget::on_stopbtn_clicked);

    // - 连接播放列表按钮信号
    connect(m_title_bar, &CTitleBar::sigClose, this, &Widget::on_title_bar_close);

    // 确保对话框在主窗口上方
    connect(m_buttom_bar->getVolumeButton(), &CVolumeButton::clicked, this, [=]()
    {
        m_buttom_bar->getVolumeButton()->getVolumeSliderDialog()->show();
        m_buttom_bar->getVolumeButton()->getVolumeSliderDialog()->raise();
    });

    // 4.连接播放列表按钮信号
    connect(m_title_bar, &CTitleBar::playlistButtonClicked, this, &Widget::on_playlist_button_clicked);

    log_info("完成connect_UI_controls");
}

// 连接任务队列信号方法
void Widget::connect_play_task_queue_signals()
{
    log_info("进入connect_play_task_queue_signals");

    // 连接播放任务队列信号
    connect(m_play_task_queue, &CPlayTaskQueue::playMediaRequested, this, &Widget::on_play_media_requested);

    // 可以添加一个定时器定期更新播放队列，或者在媒体列表变化时更新
    // 这里简单实现，假设在打开文件后更新
    connect(m_vlc_widget, &VLCWidget::hide_central_button, this, &Widget::on_update_play_task_queue);

    log_info("完成connect_play_task_queue_signals");
}

// 连接VLCWidget信号与UI更新槽
// - 连接播放进度更新信号
// - 连接时间显示更新信号
// - 连接音量更新信号
void Widget::connect_VLC_widget_signals()
{
    log_info("进入connect_VLC_widget_signals");

    // 第二类lambda函数：VLCWidget信号的响应函数，连接VLCWidget的信号到Widget的槽
    // - 由播放器内部状态变化触发，当VLC播放器改变时由VLCWidget发出信号触发，例如播放进度，音量改变时
    // - 注意第2个参数是信号，不要稀里糊涂地写为槽函数

    // 1.连接播放进度更新信号
    connect(m_vlc_widget, &VLCWidget::set_timer_slider_value, this, [=](int value)
        {
            m_buttom_bar->getTimeSlider()->setValue(value);
        }
    );

    // 2.连接时间显示更新信号
    connect(m_vlc_widget, &VLCWidget::set_timer_text, this, [=](const QString &text)
        {
            m_buttom_bar->getTimeLabel()->setText(text);
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
            int valid_value = qBound(0, value, 100);
            log_info(QString("connect响应，音量按钮信号: %1").arg(valid_value).toUtf8().data());
            m_buttom_bar->getVolumeButton()->setVolumeValue(valid_value);
            m_buttom_bar->getVolumeButton()->setVolumeLabel(QString("%1%").arg(valid_value));
        }
    );

    // 4.双击全屏
    // - 连接titlebar的双击功能
    connect(m_title_bar, &CTitleBar::doubleClicked, [this]() {
//        bool isFull = m_vlc_widget->get_is_fullscreen();
//        m_vlc_widget->toggle_full_screen(); // 调用全屏切换方法
        if (this->isFullScreen()) {
            this->showNormal();
        } else {
            this->showFullScreen();
        }
    });

    // - 连接playzone的双击功能
    connect(m_play_zone, &CPlayZone::doubleClicked, [this]() {
//        bool isFull = m_vlc_widget->get_is_fullscreen();
//        m_vlc_widget->toggle_full_screen(); // 调用全屏切换方法
        if (this->isFullScreen()) {
            this->showNormal();
        } else {
            this->showFullScreen();
        }
    });

    log_info("完成connect_VLC_widget_signals");
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
    if (m_play_zone && m_play_zone->getCentralPlayButton())
    {
        m_play_zone->getCentralPlayButton()->hide();
        log_info("中央播放按钮已隐藏");
    }
}

// 新增播放列表按钮点击槽
void Widget::on_playlist_button_clicked()
{
    log_info("播放列表按钮被点击");

    if (m_play_task_queue->isVisible())
    {
        m_play_task_queue->hideQueue();
    }
    else
    {
        // 计算播放列表面板位置（右侧）
        QPoint pos = this->mapToGlobal(QPoint(width(), 0));
        m_play_task_queue->move(pos.x(), pos.y() + m_title_bar->height());
        m_play_task_queue->setFixedHeight(height() - m_title_bar->height() - m_buttom_bar->height());
        m_play_task_queue->showQueue();
    }
}

// 新增播放媒体请求槽
void Widget::on_play_media_requested(int index)
{
//    log_info(QString("请求播放索引: %1").arg(index).toUtf8().data());
//    m_vlc_widget->on_play_media_by_index(index);
//    m_play_task_queue->setCurrentItem(index);

    log_info("播放列表按钮被点击");

    if (m_play_task_queue->isVisible())
    {
        m_play_task_queue->hideQueue();
    }
    else
    {
        m_play_task_queue->showQueue();
    }
}

// 新增更新播放队列槽
void Widget::on_update_play_task_queue()
{
    log_info("更新播放队列");
    // 从VLCWidget获取媒体列表并更新播放队列
    QStringList mediaList = m_vlc_widget->get_media_list();
    m_play_task_queue->clearQueue();

    for (int i = 0; i < mediaList.size(); ++i)
    {
        QString path = mediaList.at(i);
        QString name = QFileInfo(path).fileName();
        m_play_task_queue->addMedia(name, path);
    }

    // 设置当前播放项
    m_play_task_queue->setCurrentItem(0);
}

// 应用样式表
// - 设置各种UI元素的样式
void Widget::apply_styles()
{
    log_info("进入apply_styles");

    this->setStyleSheet(QString::fromStdString(button_qss));
    this->setStyleSheet(QString::fromStdString(logo_button_qss));
    this->setStyleSheet(QString::fromStdString(menu_qss));
    this->setStyleSheet(QString::fromStdString(minimode_qss));
    this->setStyleSheet(QString::fromStdString(settop_qss));
    this->setStyleSheet(QString::fromStdString(min_qss));
    this->setStyleSheet(QString::fromStdString(max_qss));
    this->setStyleSheet(QString::fromStdString(close_qss));
    this->setStyleSheet(QString::fromStdString(slider_qss));
    this->setStyleSheet(QString::fromStdString(time_label_qss));

    log_info("完成apply_styles");
}

void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event); // 调用父类实现，避免警告
    Q_UNUSED(event);
}
