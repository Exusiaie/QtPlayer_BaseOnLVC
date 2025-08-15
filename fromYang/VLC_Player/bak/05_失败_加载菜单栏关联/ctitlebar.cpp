#include "ctitlebar.h"
#include <QHBoxLayout>

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

CTitleBar::CTitleBar(QWidget *parent) : QWidget(parent)
{
    log_info("进入CTitleBar;");
    initUI();
}
void CTitleBar::initUI()
{
    log_info("进入initUI;");

    //禁止父窗口影响子窗口样式,必须加上，否则样式不会起作用
    setAttribute(Qt::WA_StyledBackground);

    this->setFixedHeight(32 + 10);
    this->setStyleSheet("background-color:rgb(54,54,54)");

    _plogoLabel = new QLabel(this);
    _plogoLabel->setFixedSize(32,32);
    _plogoLabel->setStyleSheet(
                "background-image:url(:/resources/titlebar/title_icon.png);border:none");

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
                "QPushButton{background-image:url(:/resources/titlebar/set.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/resources/titlebar/set_hover.svg);border:none;}");

    _pminButton = new QPushButton(this);
    _pminButton->setFixedSize(32, 32);
    _pminButton->setStyleSheet(
                "QPushButton{background-image:url(:/resources/titlebar/min.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/resources/titlebar/min_hover.svg);border:none;}");

    _pmaxButton = new QPushButton(this);
    _pmaxButton->setFixedSize(32, 32);
    _pmaxButton->setStyleSheet(
                "QPushButton{background-image:url(:/resources/titlebar/max.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/resources/titlebar/max_hover.svg);border:none;}");

    _pcloseButton = new QPushButton(this);
    _pcloseButton->setFixedSize(32, 32);
    _pcloseButton->setStyleSheet(
                "QPushButton{background-image:url(:/resources/titlebar/close.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/resources/titlebar/close_hover.svg);border:none;}");

    _pmenuButton = new QPushButton(this);
    _pmenuButton->setFixedSize(32, 32);
    _pmenuButton->setStyleSheet(
                "QPushButton{background-image:url(:/resources/file.png);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);border:none;}");

    _phLayout = new QHBoxLayout(this);
    _phLayout->addWidget(_plogoLabel);
    _phLayout->addWidget(_ptitleTextLabel);
    _phLayout->addStretch();//添加一个弹簧

    _phLayout->addWidget(_psetButton);

    // QSpacerItem* pItem1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // _phLayout->addSpacerItem(pItem1);

    _phLayout->addWidget(_pminButton);

    // QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // _phLayout->addSpacerItem(pItem2);

    _phLayout->addWidget(_pmaxButton);

    // QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // _phLayout->addSpacerItem(pItem3);

    _phLayout->addWidget(_pcloseButton);
    _phLayout->setContentsMargins(5,5,5,5);
    //this->setLayout(_phLayout);

    _phLayout->addWidget(_psetButton);

    connect(_pminButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pmaxButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pcloseButton, &QPushButton::clicked, this,&CTitleBar::onClickedSlot);

    log_info("完成initUI;");
}

void CTitleBar::setMenu(QMenu *menu)
{
    if(_pmenuButton && menu)
    {
        _pmenuButton->setMenu(menu);
    }
}

void CTitleBar::onClickedSlot()
{
    QPushButton * pbtn = qobject_cast<QPushButton*>(sender());
    QWidget * pwindow = this->window();
    if(pbtn == _pminButton) {
        pwindow->showMinimized();
    } else if(pbtn == _pmaxButton)
    {
        if(pwindow->isMaximized())
        {
            pwindow->showNormal();
            _pmaxButton->setStyleSheet(
                        "QPushButton{background-image:url(:/resources/titlebar/normal.svg);border:none}"
                        "QPushButton:hover{"
                        "background-color:rgb(99, 99, 99);"
                        "background-image:url(:/resources/titlebar/normal_hover.svg);border:none;}");
        }
        else
        {
            pwindow->showMaximized();
            _pmaxButton->setStyleSheet(
                        "QPushButton{background-image:url(:/resources/titlebar/max.svg);border:none}"
                        "QPushButton:hover{"
                        "background-color:rgb(99, 99, 99);"
                        "background-image:url(:/resources/titlebar/max_hover.svg);border:none;}");
        }
    }
    else if(pbtn == _pcloseButton)
    {
        emit sigClose();    //发射信号，通知父窗口关闭
        log_info("发出关闭窗口通知");
    }
}
