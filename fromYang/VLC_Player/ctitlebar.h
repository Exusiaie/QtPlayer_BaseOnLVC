#ifndef CTITLEBAR_H
#define CTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class CTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CTitleBar(QWidget *parent = nullptr);
    virtual ~CTitleBar() override= default;

    // 添加设置菜单的接口
    // - 由于widget禁用了子样式，因此在子样式中添加的图片无效
    void setMenu();
    // 获取播放列表按钮
    QPushButton* getPlaylistButton() const { return _pplaylistButton; }

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void sigClose();
    void playlistButtonClicked();
    void doubleClicked();                      // 发送信号通知全屏切换

public slots:
    void onClickedSlot();

private:
    void initUI();

private:
    QHBoxLayout * _phLayout;

    QLabel * _plogoLabel;
    QLabel * _ptitleTextLabel;

    QPushButton * _psetButton;
    QPushButton * _pplaylistButton;
    QPushButton * _pminButton;
    QPushButton * _pmaxButton;
    QPushButton * _pcloseButton;
//    QPushButton * _pmenuButton;
};

#endif // CTITLEBAR_H
