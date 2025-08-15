#include "cvolumebutton.h"

#include <QDebug>
#include <QLabel>
#include <QString>
#include <QCursor>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QVBoxLayout>

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

CVolumeButton::CVolumeButton(QWidget *parent)
    : QPushButton(parent)
    , _pvolumeSliderDlg(nullptr)
{
//    this->setFixedSize(32,32);

//    setStyleSheet("QPushButton{background-image:url(:/resources/audio_open.svg);border:none;}"
//                  "QPushButton:hover{background-image:url(:/resources/audio_open_hover.svg);border:none;}"
//                  "QPushButton:pressed{background-image:url(:/resources/audio_open.svg);border:none;}"
//                  );

    InitVolumeButton();
}

CVolumeButton::~CVolumeButton(){}

void CVolumeButton::enterEvent(QEvent *event)
{
    log_info("CVolumeButton::enterEvent()");

    if (!_pvolumeSliderDlg)
    {
        InitVolumeButton();
    }

    // 计算对话框设置
    QPoint p1 = this->mapToGlobal(QPoint(0, 0)); // 声音按钮左上角相对于屏幕的绝对位置
    QRect rect1 = this->rect();
    QRect rect2 = _pvolumeSliderDlg->rect();     // rect包含标题栏，去掉标题栏后height不变

    int x = p1.x() + (rect1.width() - rect2.width()) / 2;
    int y = p1.y() - rect2.height() - 5;
    _pvolumeSliderDlg->move(x, y);               // move是相对于桌面原点的位置
    _pvolumeSliderDlg->show();

    // 启动定时器，每隔500ms检查一次
    if(_timerId <= 0 || _isRunning == false)
    {
        _timerId = startTimer(500);
        _isRunning = true;
    }
}

void CVolumeButton::paintEvent(QPaintEvent* paintEvent)
{
    log_info("CVolumeButton::paintEvent");
    QStylePainter p(this);
    QStyleOptionButton option;
    initStyleOption(&option);
    p.drawControl(QStyle::CE_PushButton, option);
}

//void CVolumeButton::leaveEvent(QEvent *event)
//{
//    qDebug() << "CVolumeButton::leaveEvent";
//    hide();
//}

void CVolumeButton::timerEvent(QTimerEvent *)
{
    log_info("CVolumeButton::timerEvent");
    hideVolumeDialog();
}

void CVolumeButton::mousePressEvent(QMouseEvent *event)
{
    log_info("进入CVolumeButton::mousePressEvent");
    if(event->button() == Qt::LeftButton)
    {
        _isMute = !_isMute;
        if(_isMute) {   // 设置静音
            if(_pvolumeSliderDlg) {
                //保存原来的音量值
                _volumeValue = _pvolumeSliderDlg->getSliderValue();
                _pvolumeSliderDlg->setSliderValue(0);
//                setStyleSheet("QPushButton{background-image:url(:/resources/audio_mute.svg)}");
                this->setIcon(QIcon(":/resources/audio_mute.svg"));
                if(_volumeLabel)
                {
                    _volumeLabel->setText(QString("音量: 0%"));
                    log_info("设置静音标签");
                } else {
                    log_error("_volumeLabel为空，无法更新静音标签");
                }

//                emit volumeChanged(0);  // 真正起作用的只有这个
                emit _pvolumeSliderDlg->getSlider()->valueChanged(0);  // 真正起作用的只有这个
            }
        } else {        // 取消静音
            if(_pvolumeSliderDlg)
            {
                _pvolumeSliderDlg->setSliderValue(_volumeValue);
//                setStyleSheet(
//                    "QPushButton{background-image:url(:/resources/audio_open.svg);border:none;}"
//                    "QPushButton:hover{background-image:url(:/resources/audio_open_hover.svg);border:none;}"
//                    "QPushButton:pressed{background-image:url(:/resources/audio_open.svg);border:none;}"
//                );
                this->setIcon(QIcon(":/resources/audio_open.svg"));
                if(_volumeLabel) {
                    _volumeLabel->setText(QString("音量: %1%").arg(_volumeValue));
                    log_info(QString("设置音量标签: %1").arg(_volumeValue).toUtf8().data());
                } else {
                    log_error("_volumeLabel为空，无法更新音量标签");
                }

//                emit volumeChanged(_volumeValue);
                emit _pvolumeSliderDlg->getSlider()->valueChanged(_volumeValue);  // 真正起作用的只有这个
            }
        }
    }
    // 其他鼠标按钮事件传递给父类
    QPushButton::mousePressEvent(event);
    log_info(QString("离开CVolumeButton::mousePressEvent，目前音量: %1").arg(_volumeValue).toUtf8().data());
}

void CVolumeButton::InitVolumeButton()
{

    if (!_pvolumeSliderDlg)
    {
        // 初始化实例
        _pvolumeSliderDlg = new CVolumeSliderDialog(this);

        // 设置初始音量
        _pvolumeSliderDlg->setSliderValue(_volumeValue);

        // 设置音量标签（还没找到应该加在哪里，没有加入布局）
        // - 先不要添加，格式容易有问题
        _volumeLabel = new QLabel(QString("音量, %1%").arg(_volumeValue));
        log_info(QString("创建音量标签: %1").arg(_volumeValue).toUtf8().data());
        // - 本来想设置格式，发现没有什么用
//        _volumeLabel->setAlignment(Qt::AlignCenter);
//        _volumeLabel->setStyleSheet("color: white; background-color: padding: 4px;");

        // 获取滑块并设置音量
        QSlider *slider = _pvolumeSliderDlg->getSlider();
        slider->setParent(_pvolumeSliderDlg);
        _pvolumeSliderDlg->setSliderValue(_volumeValue);

        // 设置图标样式
        this->setIconSize(QSize(24, 24)); // 设置图标大小
        this->setIcon(QIcon(":/resources/audio_open.svg"));

//        // 连接滑块值变化信号
//        connect(_pvolumeSliderDlg, &CVolumeSliderDialog::valueChanged, this, [=](int value) {
//            _volumeValue = value;
//            _volumeLabel->setText(QString("音量: %1%").arg(value));
//            emit volumeChanged(value);
//        });

//        // 调整对话框布局
//        QVBoxLayout *layout = new QVBoxLayout(containerWidget);
//        layout->setContentsMargins(5, 5, 5, 5);
//        layout->setSpacing(5);
//        layout->addWidget(_volumeLabel);
//        layout->addWidget(slider);
//        _pvolumeSliderDlg->setLayout(layout);

//        // 设置容器部件为对话框的中心部件
//        // - cvolumebutton.cpp:69:28: error: no member named 'setCentralWidget' in 'CVolumeSliderDialog'
//        _pvolumeSliderDlg->setCentralWidget(containerWidget);

    }

}

void CVolumeButton::hideVolumeDialog()
{
    if(_pvolumeSliderDlg !=nullptr && _pvolumeSliderDlg->isVisible())
    {
        QPoint mousePos = QCursor::pos();//获取鼠标的位置
        QRect rect1 = _pvolumeSliderDlg->geometry();
        QRect rect2 = this->geometry();
        QRect rect3(rect1.x(), rect1.y(), rect1.width(), rect1.height() + rect2.height());

        //根据鼠标的位置判断音量大小窗口是否消失
        if(!rect3.contains(mousePos)) {
            _pvolumeSliderDlg->hide();
            log_info(">> hide volume dialog...");
        }
    }
    else
    {
        killTimer(_timerId);//当不包含鼠标位置，并且音量控制界面没显示时，就停止定时器
        _isRunning = false;
    }
}

/*  // 目前还没想到有甚么用处
void CVolumeButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "MyWidget::mouseReleaseEvent(QMouseEvent*)\n";
}

bool CVolumeButton::event(QEvent *event)
{
    //qDebug() << "event";
    if(event->type() == QEvent::KeyPress)
    {
        qDebug() << "222 " << objectName() <<" == KeyPress";
        //return true;
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "222 " << objectName() << " == MousePress";
        //return true;//返回值为true时，阻止事件向父对象传递
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        qDebug() << "222" << objectName() << " == MouseRelease";
        //return true;
    }
    return QWidget::event(event);//向父对象传递事件的处理
}

bool CVolumeButton::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        qDebug() << "Filter1:" << watched->objectName() << "MousePress";
    }
    return false;//返回false表示事件还会交给目标对象处理
}
*/
