#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <QWidget>
#include <vlc/vlc.h>  // 假设需要包含VLC头文件

class VLCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VLCWidget(QWidget *parent = nullptr);
    ~VLCWidget();

    // 消息传递相关方法
    void sendMessage(const QString &message);
    QString receiveMessage();

signals:
    void messageReceived(const QString &message);

private:
    // VLC相关成员变量
    libvlc_instance_t *m_vlcInstance;
    // 其他必要成员
};

#endif // VLCWIDGET_H