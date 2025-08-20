#include "CVolumeButton.h"
#include <QDebug>
#include <QStylePainter>
#include <QStyleOptionButton>


CVolumeButton::CVolumeButton(QWidget *parent)
    : QPushButton(parent)
{
    _pvolumeSliderDlg = new CVolumeSliderDialog(this);


    this->setFixedSize(32,32);
    setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/audio_open.svg);border:none;}"
                  "QPushButton:hover{background-image:url(:/Resource/playctrlBar/audio_open_hover.svg);border:none;}"
                  "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/audio_open.svg);border:none;}");

    connect(_pvolumeSliderDlg, &CVolumeSliderDialog::sliderValueChanged, this, &CVolumeButton::sliderValueChanged);
}
CVolumeButton::~CVolumeButton()
{}
void CVolumeButton::enterEvent(QEvent *event)
{
   // qDebug() << "CVolumeButton::enterEvent()";
    if (!_pvolumeSliderDlg)
        _pvolumeSliderDlg = new CVolumeSliderDialog(this);
    QPoint p1 = this->mapToGlobal(QPoint(0, 0)); //声音按钮左上角相对于屏幕的绝对位置
    QRect rect1 = this->rect();
    QRect rect2 = _pvolumeSliderDlg->rect(); //rect包含标题栏，去掉标题栏后height不变
    int x = p1.x() +(rect1.width() - rect2.width()) / 2;
    int y = p1.y() - rect2.height();
    _pvolumeSliderDlg->move(x, y); //move是相对于桌面原点的位置
    _pvolumeSliderDlg->show();
    //一旦音量控制界面出现后，就开启定时器
    if(_isRunning == false) {
        _timerId = startTimer(250);//开启定时器,250毫秒的时间间隔
        _isRunning = true;//定时器启动标志位
    }
}

void CVolumeButton::timerEvent(QTimerEvent *)
{
    qDebug() << "CVolumeButton::timerEvent";
    hide();
}



void CVolumeButton::hide()
{
    if(_pvolumeSliderDlg !=nullptr && _pvolumeSliderDlg->isVisible()) {
        QPoint mousePos = QCursor::pos();//获取鼠标的位置
        QRect rect1 = _pvolumeSliderDlg->geometry();
        QRect rect2 = this->geometry();
        QRect rect3(rect1.x(), rect1.y(), rect1.width(), rect1.height() +
                    rect2.height());
        //根据鼠标的位置判断音量大小窗口是否消失
        if(!rect3.contains(mousePos)) {
            _pvolumeSliderDlg->hide();
            qDebug() << ">> hide...";
        }
    } else {
        killTimer(_timerId);//当不包含鼠标位置，并且音量控制界面没显示时，就停止定时器
        _isRunning = false;
    }
}

void CVolumeButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        _isMute = !_isMute;
        if(_isMute) {//设置为静音
            if(_pvolumeSliderDlg) {
                //保存原来的音量值
                 _volumeValue = _pvolumeSliderDlg->value();
                _pvolumeSliderDlg->setSliderValue(0);
                setStyleSheet("QPushButton{background-image:url(:/Resource/playctrlBar/audio_mute.svg);border:none;}");

            }
        } else {
            if(_pvolumeSliderDlg) {
                _pvolumeSliderDlg->setSliderValue(_volumeValue);
                setStyleSheet(
                            "QPushButton{background-image:url(:/Resource/playctrlBar/audio_open.svg);border:none;}"
                            "QPushButton:hover{background-image:url(:/Resource/playctrlBar/audio_open_hover.svg);border:none;}"
                            "QPushButton:pressed{background-image:url(:/Resource/playctrlBar/audio_open.svg);border:none;}");
            }
        }
    }

}
