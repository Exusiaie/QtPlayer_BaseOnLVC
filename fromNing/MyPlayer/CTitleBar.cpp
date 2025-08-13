#include "CTitleBar.h"
#include <qt_windows.h>
#include <QHBoxLayout>

CTitleBar::CTitleBar(QWidget *parent) : QWidget(parent)
{
    initUI();
}

#if 1
void CTitleBar::mousePressEvent(QMouseEvent * event)
{
    //按住鼠标后拖动窗口的实现
    if (ReleaseCapture())
    {
        QWidget * pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
}
#endif

void CTitleBar::initUI()
{
    //禁止父窗口影响子窗口样式,必须加上，否则样式不会起作用
    setAttribute(Qt::WA_StyledBackground);

    this->setFixedHeight(32 + 10);
    this->setStyleSheet("background-color:rgb(54,54,54)");

    _plogoLabel = new QLabel(this);
    _plogoLabel->setFixedSize(32,32);
    _plogoLabel->setStyleSheet(
            "border-image:url(:/Resource/titlebar/title_icon.png);border:none");

    _ptitleTextLabel = new QLabel(this);
    _ptitleTextLabel->setText("我是标题");
    _ptitleTextLabel->setFixedWidth(120);
    _ptitleTextLabel->setStyleSheet(
            "QLabel{font-family: Microsoft YaHei;"
                "font-size:18px;"
                "color:#BDC8E2;background-color:rgb(54,54,54);}");

    _psetButton = new QPushButton(this);
    _psetButton->setFixedSize(32, 32);
    _psetButton->setStyleSheet(
            "QPushButton{border-image:url(:/Resource/titlebar/set.svg);border:none}"
            "QPushButton:hover{"
                    "background-color:rgb(199, 99, 99);"
                    "border-image:url(:/Resource/titlebar/set_hover.svg);border:none;}");

    _pminButton = new QPushButton(this);
    _pminButton->setFixedSize(32, 32);
    _pminButton->setStyleSheet(
            "QPushButton{border-image:url(:/Resource/titlebar/min.svg);border:none}"
            "QPushButton:hover{"
                    "background-color:rgb(99, 99, 99);"
                    "border-image:url(:/Resource/titlebar/min_hover.svg);border:none;}");

    _pmaxButton = new QPushButton(this);
    _pmaxButton->setFixedSize(32, 32);
    _pmaxButton->setStyleSheet(
            "QPushButton{border-image:url(:/Resource/titlebar/max.svg);border:none}"
            "QPushButton:hover{"
                    "background-color:rgb(99, 99, 99);"
                    "border-image:url(:/Resource/titlebar/max_hover.svg);border:none;}");

    _pcloseButton = new QPushButton(this);
    _pcloseButton->setFixedSize(32, 32);
    _pcloseButton->setStyleSheet(
            "QPushButton{border-image:url(:/Resource/titlebar/close.svg);border:none}"
            "QPushButton:hover{"
                    "background-color:rgb(99, 99, 99);"
                    "border-image:url(:/Resource/titlebar/close_hover.svg);border:none;}");

    QHBoxLayout * phLayout = new QHBoxLayout(this);
    phLayout->addWidget(_plogoLabel);
    phLayout->addWidget(_ptitleTextLabel);
    phLayout->addStretch();//添加一个弹簧

    phLayout->addWidget(_psetButton);

    QSpacerItem* pItem1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    phLayout->addSpacerItem(pItem1);

    phLayout->addWidget(_pminButton);

//    QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
//    phLayout->addSpacerItem(pItem2);

    phLayout->addWidget(_pmaxButton);

//    QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
//    phLayout->addSpacerItem(pItem3);

    phLayout->addWidget(_pcloseButton);
    phLayout->setContentsMargins(5,5,5,5);

    connect(_pminButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pmaxButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pcloseButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
}

void CTitleBar::onClickedSlot()
{
    QPushButton * pbtn = qobject_cast<QPushButton*>(sender());
    QWidget * pwindow = this->window();//获取顶级窗口
    if(pbtn == _pminButton) {
        pwindow->showMinimized();
    } else if(pbtn == _pmaxButton) {
        if(pwindow->isMaximized()) {
            pwindow->showNormal();
            _pmaxButton->setStyleSheet(
                    "QPushButton{border-image:url(:/Resource/titlebar/normal.svg);border:none}"
                    "QPushButton:hover{"
                            "background-color:rgb(99, 99, 99);"
                            "border-image:url(:/Resource/titlebar/normal_hover.svg);border:none;}");
        } else  {
            pwindow->showMaximized();
            _pmaxButton->setStyleSheet(
                    "QPushButton{border-image:url(:/Resource/titlebar/max.svg);border:none}"
                    "QPushButton:hover{"
                            "background-color:rgb(99, 99, 99);"
                            "border-image:url(:/Resource/titlebar/max_hover.svg);border:none;}");
        }
    } else if(pbtn == _pcloseButton) {
        emit sigClose();//发射信号，通知父窗口关闭
        //pwindow->close();
    }
}
