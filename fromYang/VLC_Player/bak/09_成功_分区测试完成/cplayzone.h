#ifndef CPLAYZONE_H
#define CPLAYZONE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

class CPlayZone : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayZone(QWidget *parent = nullptr);
    QPushButton* getCentralPlayButton() const; // 提供访问中央播放按钮的方法

signals:
    void centralButtonClicked(); // 转发中央按钮点击信号

private:
    QPushButton *m_central_play_button; // 中央播放按钮

private slots:
    void onCentralButtonClicked(); // 中央按钮点击处理
};

#endif // CPLAYZONE_H
