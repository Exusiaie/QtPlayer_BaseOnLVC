#include "cplaytaskqueue.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QStringList>
#include <QListWidgetItem>

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

CPlayTaskQueue::CPlayTaskQueue(QWidget *parent) : QWidget(parent)
{
    // 设置窗口属性
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setFixedWidth(300);
    setStyleSheet("background-color: rgb(54, 54, 54); color: white;");

    // 创建列表控件
    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet(
        "QListWidget { background-color: transparent; border: none; }"
        "QListWidget::item { padding: 8px; border-bottom: 1px solid rgb(70, 70, 70); }"
        "QListWidget::item:selected { background-color: rgb(70, 70, 70); }"
        "QListWidget::item:hover { background-color: rgb(60, 60, 60); }"
    );

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_listWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // 初始化定时器
    m_hideTimer = nullptr;
    m_timerId = 0;
    m_isMouseInside = false;

    // 连接列表项点击信号
    connect(m_listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item)
    {
        int index = m_listWidget->row(item);
        emit playMediaRequested(index);
    });

    log_info("播放任务队列初始化完成");
}

CPlayTaskQueue::~CPlayTaskQueue()
{
    if (m_timerId > 0)
    {
        killTimer(m_timerId);
    }
    if (m_hideTimer)
    {
        delete m_hideTimer;
        m_hideTimer = nullptr;
    }
    log_info("播放任务队列已销毁");
}

void CPlayTaskQueue::addMedia(const QString &name, const QString &path)
{
    QListWidgetItem *item = new QListWidgetItem(name);
    item->setData(Qt::UserRole, path);
    m_listWidget->addItem(item);
    log_info(QString("添加媒体到队列: %1").arg(name).toUtf8().data());
}

void CPlayTaskQueue::clearQueue()
{
    m_listWidget->clear();
    log_info("播放队列已清空");
}

void CPlayTaskQueue::setCurrentItem(int index)
{
    if (index >= 0 && index < m_listWidget->count())
    {
        m_listWidget->setCurrentRow(index);
        log_info(QString("设置当前播放项: %1").arg(index).toUtf8().data());
    }
}

void CPlayTaskQueue::showQueue()
{
    show();
    raise();
    m_isMouseInside = true;
    log_info("播放队列已显示");
}

void CPlayTaskQueue::hideQueue()
{
    hide();
    log_info("播放队列已隐藏");
}

void CPlayTaskQueue::enterEvent(QEvent *event)
{
    log_info("鼠标进入播放队列");
    m_isMouseInside = true;
    if (m_timerId > 0)
    {
        killTimer(m_timerId);
        m_timerId = 0;
    }
    QWidget::enterEvent(event);
}

void CPlayTaskQueue::leaveEvent(QEvent *event)
{
    log_info("鼠标离开播放队列");
    m_isMouseInside = false;
    // 启动3秒定时器
    if (m_timerId == 0)
    {
        m_timerId = startTimer(3000);
    }
    QWidget::leaveEvent(event);
}

void CPlayTaskQueue::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId && !m_isMouseInside)
    {
        log_info("定时器触发，隐藏播放队列");
        hideQueue();
        killTimer(m_timerId);
        m_timerId = 0;
    }
    QWidget::timerEvent(event);
}
