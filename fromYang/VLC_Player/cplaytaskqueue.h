#ifndef CPLAYTASKQUEUE_H
#define CPLAYTASKQUEUE_H

#include <QWidget>
#include <QListWidget>
#include <QTimer>
#include <QMouseEvent>

class CPlayTaskQueue : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayTaskQueue(QWidget *parent = nullptr);
    ~CPlayTaskQueue();

    // 添加媒体到队列
    void addMedia(const QString &name, const QString &path);
    // 清空队列
    void clearQueue();
    // 设置当前播放项
    void setCurrentItem(int index);
    // 显示队列
    void showQueue();
    // 隐藏队列
    void hideQueue();

signals:
    // 请求播放指定索引的媒体
    void playMediaRequested(int index);

protected:
    // 重写鼠标事件
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    QListWidget *m_listWidget;  // 显示播放列表
    QTimer *m_hideTimer;        // 隐藏定时器
    int m_timerId;              // 定时器ID
    bool m_isMouseInside;       // 鼠标是否在窗口内
};

#endif // CPLAYTASKQUEUE_H
