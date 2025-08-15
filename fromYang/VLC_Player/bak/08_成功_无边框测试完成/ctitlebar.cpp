#include "ctitlebar.h"
#include <QHBoxLayout>
#include <QMenu>
#include <QFileDialog>

#define log_info(msg) \
    qDebug("%s | %d | %s : %s", __FILE__, __LINE__, __FUNCTION__, msg);
#define log_error(msg) \
    qCritical("%s | %d | %s : [ERROR] %s", __FILE__, __LINE__, __FUNCTION__, msg);

CTitleBar::CTitleBar(QWidget *parent) : QWidget(parent)
{
    log_info("进入CTitleBar;");
    initUI();
    setMenu();
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
                "image:url(:/resources/titlebar/title_icon.png);border:none");

    _ptitleTextLabel = new QLabel(this);
    _ptitleTextLabel->setText("我是标题");
    _ptitleTextLabel->setFixedWidth(120);
    _ptitleTextLabel->setStyleSheet(
                "QLabel{font-family: Microsoft YaHei;"
                "font-size:18px;"
                "color:#BDC8E2;background-color:rgb(54,54,54);}");

    _psetButton = new QPushButton(this);
    _psetButton->setFixedSize(32, 32);
    _psetButton->setIcon(QIcon(":/resources/titlebar/set.svg"));
    _psetButton->setIconSize(QSize(24, 24)); // 设置图标大小

    _pminButton = new QPushButton(this);
    _pminButton->setFixedSize(32, 32);
    _pminButton->setIcon(QIcon(":/resources/titlebar/min.svg"));
    _pminButton->setIconSize(QSize(24, 24)); // 设置图标大小

    _pmaxButton = new QPushButton(this);
    _pmaxButton->setFixedSize(32, 32);
    _pmaxButton->setIcon(QIcon(":/resources/titlebar/max.svg"));
    _pmaxButton->setIconSize(QSize(24, 24)); // 设置图标大小

    _pcloseButton = new QPushButton(this);
    _pcloseButton->setFixedSize(32, 32);
    _pcloseButton->setIcon(QIcon(":/resources/titlebar/close.svg"));
    _pcloseButton->setIconSize(QSize(24, 24)); // 设置图标大小


//    _psetButton = new QPushButton(this);
//    _psetButton->setFixedSize(32, 32);
//    _psetButton->setStyleSheet(
//                "QPushButton{background-image:url(:/resources/titlebar/set.svg);border:none}"
//                "QPushButton:hover{"
//                "background-color:rgb(99, 99, 99);"
//                "background-image:url(:/resources/titlebar/set_hover.svg);border:none;}");

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

//    _phLayout->addWidget(_psetButton);

    connect(_pminButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pmaxButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pcloseButton, &QPushButton::clicked, this,&CTitleBar::onClickedSlot);

    log_info("完成initUI;");
}

// 初始化菜单栏
// - 创建菜单
// - 设置菜单图标和快捷键
// - 创建菜单项
// - 连接菜单信号
void CTitleBar::setMenu()
{
    log_info("进入initialize_menu();");

    // 1.创建菜单栏
    QMenu * file_menu_items = new QMenu(this);
    file_menu_items->setIcon(QIcon(":/resources/file.png"));
    file_menu_items->setTitle("文件");

    // 2.设置菜单图标和快捷键
    QList<QAction *> fileAcList;

    QAction * openFileAc = new QAction(QIcon(":/resources/file.png"), "打开文件", this);
    openFileAc->setShortcut(QKeySequence("Ctrl+8"));// 设置快捷键
    QAction * openFolderAc = new QAction("打开文件夹", this);
    QAction * openUrlAc = new QAction("打开url", this);

    fileAcList << openFileAc << openFolderAc << openUrlAc;

    file_menu_items->addActions(fileAcList);//添加二级子菜单

    // 3.创建菜单项
    QMenu * menu = new QMenu;//主菜单
    menu->addMenu(file_menu_items);//添加一级子菜单

    QAction * playAc = new QAction(QIcon(":/resources/play.png"), "播放", this);
    QAction * toolsAc = new QAction(QIcon(":/resources/tools.png"), "工具",this);

    menu->addAction(playAc);
    menu->addAction(toolsAc);

    menu->addSeparator();//添加分隔线

    QMenu * setMenuItems = new QMenu;
    setMenuItems->setTitle("设置");
    setMenuItems->setIcon(QIcon(":/resources/set.png"));
    QList<QAction*> setAcList;
    QAction * sysSetAc = new QAction("系统设置", this);
    QAction * playSetAc = new QAction("播放设置", this);
    QAction * captionSetAc = new QAction("字幕设置", this);

    setAcList << sysSetAc << playSetAc << captionSetAc;

    setMenuItems->addActions(setAcList);
    menu->addMenu(setMenuItems);

    menu->addSeparator();//添加分隔线

    QAction * exitAc = new QAction(QIcon(":/resources/exit.png"), "退出", this);
    menu->addAction(exitAc);
    _psetButton->setMenu(menu);//在按钮上设置菜单

    log_info("完成菜单设置，准备进行关联");

    // 5.连接菜单信号
    connect(openFileAc, &QAction::triggered,
        [=]{
            QString fileName = QFileDialog::getOpenFileName(this, "请选择视频文件", "D:/", "视频(*.mp4);;""视频(*.avi);;");
            if(fileName.isEmpty()) { return; }
        }
    );

    log_info("完成initialize_menu();");
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
