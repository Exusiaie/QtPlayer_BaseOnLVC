#include "CVolumeButton.h"
#include <QDebug>
#include <QStylePainter>
#include <QStyleOptionButton>
CVolumeButton::CVolumeButton(QWidget *parent)
    : QPushButton(parent)
    , _pvolumeSliderDlg(nullptr)
{
    this->setFixedSize(32,32);
    setStyleSheet("QPushButton{backgroundimage:url(:/resources/audio_open.svg);border:none;}"
                  "QPushButton:hover{backgroundimage:url(:/resources/audio_open_hover.svg);border:none;}"
                  "QPushButton:pressed{backgroundimage:url(:/resources/audio_open.svg);border:none;}");
}
CVolumeButton::~CVolumeButton()
{}
void CVolumeButton::enterEvent(QEvent *event)
{
    qDebug() << "CVolumeButton::enterEvent()";
    if (!_pvolumeSliderDlg)
        _pvolumeSliderDlg = new CVolumeSliderDialog(this);
    QPoint p1 = this->mapToGlobal(QPoint(0, 0)); //声音按钮左上角相对于屏幕的绝对位置
    QRect rect1 = this->rect();
    QRect rect2 = _pvolumeSliderDlg->rect(); //rect包含标题栏，去掉标题栏后height不变

    int x = p1.x() + (rect1.width() - rect2.width()) / 2;
    int y = p1.y() - rect2.height() - 5;
    _pvolumeSliderDlg->move(x, y); //move是相对于桌面原点的位置
    _pvolumeSliderDlg->show();
}
void CVolumeButton::paintEvent(QPaintEvent*)
{
    qDebug() << "CVolumeButton::paintEvent";
    QStylePainter p(this);
    QStyleOptionButton option;
    initStyleOption(&option);
    p.drawControl(QStyle::CE_PushButton, option);
}

void CVolumeButton::leaveEvent(QEvent *event)
{
    qDebug() << "CVolumeButton::leaveEvent";
    hide();
}

void CVolumeButton::hide()
{
    if(_pvolumeSliderDlg) {
        //根据鼠标的位置判断音量大小窗口是否消失
        QPoint mousePos = QCursor::pos();//获取鼠标的位置
        QRect rect = _pvolumeSliderDlg->geometry();
        if(!rect.contains(mousePos) && _pvolumeSliderDlg->isVisible()) {
            _pvolumeSliderDlg->hide();
            qDebug() << ">> hide...";
        }
    }
}
