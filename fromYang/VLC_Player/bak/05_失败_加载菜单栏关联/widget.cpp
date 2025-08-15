#include "vlcwidget.h"
#include "widget.h"
#include "qss.h"

#include "ctitlebar.h"

#include <string>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QLabel>
#include <QFrame>
#include <QMenu>

using std::string;

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

Widget::Widget(QWidget *parent)
    : CFramelessWidget(parent)
{
    initialize_basic_UI();
    initialize_menu();
    initialize_control_panel();
    connect_UI_controls();
    connect_VLC_widget_signals();
    apply_styles();
}

Widget::~Widget()
{
    // 释放按钮资源
    delete m_open_button;
    delete m_play_button;
    delete m_pause_button;
    delete m_stop_button;
    delete m_title_bar;
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
    m_menu_button = new QPushButton("菜单");
    m_menu_button->setFixedWidth(80);
    title_layout->addWidget(m_menu_button);
    title_layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 强制左对齐，垂直居中
*/

    // 4.创建控制窗口（播放区域）
    QWidget *control_window = new QWidget(this);
    m_vlc_widget->set_video_widget(control_window);
    log_info("完成m_vlc_widget创建");

    // 5.添加到主布局
    //m_main_layout->addLayout(m_title_bar->getHLayout());  // 会报错
    m_main_layout->addWidget(m_title_bar);
    m_main_layout->addWidget(control_window, 1);
    log_info("完成initialize_basic_UI;");
}

// 初始化菜单栏
// - 创建菜单
// - 设置菜单图标和快捷键
// - 创建菜单项
// - 连接菜单信号
void Widget::initialize_menu()
{
    log_info("进入initialize_menu();");

    // 1.创建菜单栏
    QMenu * file_menu_items = new QMenu;
    file_menu_items->setIcon(QIcon(":/resources/file.png"));
    file_menu_items->setTitle("文件");

    // 2.设置菜单图标和快捷键
    QList<QAction *> fileAcList;

    QAction * openFileAc = new QAction(QIcon(":/resources/file.png"), "打开文件", this);
    openFileAc->setShortcut(QKeySequence("Ctrl+8"));// 设置快捷键
    QAction * openFolderAc = new QAction("打开文件夹", this);
    QAction * openUrlAc = new QAction("打开url", this);

    fileAcList << openFileAc << openFolderAc << openUrlAc;

    file_menu_items->addActions(fileAcList);//添加二级子菜单

    // 3.创建菜单项
    QMenu * menu = new QMenu;//主菜单
    menu->addMenu(file_menu_items);//添加一级子菜单

    QAction * playAc = new QAction(QIcon(":/resources/play.png"), "播放", this);
    QAction * toolsAc = new QAction(QIcon(":/resources/tools.png"), "工具",this);

    menu->addAction(playAc);
    menu->addAction(toolsAc);

    menu->addSeparator();//添加分隔线

    QMenu * setMenuItems = new QMenu;
    setMenuItems->setTitle("设置");
    setMenuItems->setIcon(QIcon(":/resources/set.png"));
    QList<QAction*> setAcList;
    QAction * sysSetAc = new QAction("系统设置", this);
    QAction * playSetAc = new QAction("播放设置", this);
    QAction * captionSetAc = new QAction("字幕设置", this);

    setAcList << sysSetAc << playSetAc << captionSetAc;

    setMenuItems->addActions(setAcList);
    menu->addMenu(setMenuItems);

    menu->addSeparator();//添加分隔线

    QAction * exitAc = new QAction(QIcon(":/resources/exit.png"), "退出", this);
    menu->addAction(exitAc);
    m_menu_button->setMenu(menu);//在按钮上设置菜单

    log_info("完成菜单设置，准备进行关联");

    // 4.将菜单逻辑关联至ctitlebar.h中实现
    m_title_bar->setMenu(menu);

    // 5.连接菜单信号
    connect(openFileAc, &QAction::triggered,
        [=]{
            QString fileName = QFileDialog::getOpenFileName(this, "请选择视频文件", "D:/", "视频(*.mp4);;""视频(*.avi);;");
            if(fileName.isEmpty()) { return; }
        }
    );

    log_info("完成initialize_menu();");
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

    // - 创建音量滑块与音量显示
    m_volume_slider = new QSlider(Qt::Horizontal);
    m_volume_slider->setRange(0, 100);
    m_volume_slider->setValue(20);      // 默认音量20%
    m_volume_label = new QLabel("音量");

    // 4.设置底部按钮
    // - 底部按钮布局（保持距离，均分，留白）
    // - 上下两层，上层时间进度条，下层按钮与音量
    QVBoxLayout *bottomLayout = new QVBoxLayout(buttom_bar);
    // - 如果指定父部件，会引发报错：QLayout: Attempting to add QLayout to QWidget which already has a layout
    // - 错误原因是创建布局时多次指定了相同的父部件
    QHBoxLayout *firstLayer = new QHBoxLayout();    // 不指定父部件
    QHBoxLayout *secondLayer = new QHBoxLayout();
    //bottomLayout->setContentsMargins(10, 5, 10, 5);

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
    connect(m_volume_slider, &QSlider::valueChanged, this, [=](int value)
        {
            libvlc_audio_set_volume(m_vlc_widget->get_media_player(), value);          // 显示位置
            m_volume_label->setText(QString("音量: %1%").arg(value));
        }
    );

    // 3.连接按钮信号
    connect(m_open_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_openbtn_clicked);
    connect(m_play_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_playbtn_clicked);
    connect(m_pause_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_pausebtn_clicked);
    connect(m_stop_button, &QPushButton::clicked, m_vlc_widget, &VLCWidget::on_stopbtn_clicked);
    connect(m_title_bar, &CTitleBar::sigClose, this, &Widget::on_title_bar_close);

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
    connect(m_vlc_widget, &VLCWidget::set_volume_slider_value, this, [=](int value)
        {
            m_volume_slider->setValue(value);
            m_volume_label->setText(QString("音量: %1%").arg(value));
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

    if(m_vlc_widget)
    {
        delete m_vlc_widget;
        close();
        log_info("完成on_title_bar_close()");
    }
}
