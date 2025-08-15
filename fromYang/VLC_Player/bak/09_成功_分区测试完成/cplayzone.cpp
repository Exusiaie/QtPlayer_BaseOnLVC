// ... existing code ...
#include "cplayzone.h"

#include <QPixmap>

// 日志宏定义
#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);

CPlayZone::CPlayZone(QWidget *parent) : QWidget(parent)
{
    // 1.创建中央播放按钮
    m_central_play_button = new QPushButton(this);

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
    QVBoxLayout *central_layout = new QVBoxLayout(this);
    central_layout->addWidget(m_central_play_button, 0, Qt::AlignCenter);

    // 5.连接信号
    connect(m_central_play_button, &QPushButton::clicked, this, &CPlayZone::onCentralButtonClicked);

    log_info("完成CPlayZone初始化");
}

QPushButton* CPlayZone::getCentralPlayButton() const
{
    return m_central_play_button;
}

void CPlayZone::onCentralButtonClicked()
{
    emit centralButtonClicked();
}
