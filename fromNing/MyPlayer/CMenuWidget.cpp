#include "CMenuWidget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QCursor>
#include <QDebug>

CMenuWidget::CMenuWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setWindowFlags(Qt::FramelessWindowHint);


    // 调用初始化函数
    initMenuBar();
//    initRightMenu();

    // 创建一个垂直布局来容纳菜单栏和右键菜单
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
      _pVLCKits = new VLCKits(this);
    mainLayout->addWidget(_pmenuBar);

    mainLayout->addStretch();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    this->setStyleSheet("background-color:rgb(208, 208, 208)");
}

CMenuWidget::~CMenuWidget()
{
    // QObject 的父子关系会自动处理子对象的内存释放
}

// ------------------- 初始化菜单栏 -------------------
void CMenuWidget::initMenuBar()
{
    _pmenuBar = new QMenuBar(this);

    // 创建"文件"菜单
    QMenu *fileMenu = _pmenuBar->addMenu("文件");
    QAction *newAction = new QAction("新建", this);
    newAction->setShortcut(Qt::CTRL | Qt::Key_N); // 设置快捷键
    fileMenu->addAction(newAction);
    fileMenu->addSeparator(); // 添加分隔符
    QAction *openAction = new QAction("打开", this);
    fileMenu->addAction(openAction);

    // 创建"编辑"菜单
    QMenu *editMenu = _pmenuBar->addMenu("编辑");
    QAction *copyAction = new QAction("复制", this);
    QAction *pasteAction = new QAction("粘贴", this);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    // 连接信号到槽
    connect(newAction, &QAction::triggered, this, &CMenuWidget::onNewActionTriggered);
    connect(openAction, &QAction::triggered, this, &CMenuWidget::onOpenActionTriggered);
    connect(copyAction, &QAction::triggered, this, &CMenuWidget::onCopyActionTriggered);
    connect(pasteAction, &QAction::triggered, this, &CMenuWidget::onPasteActionTriggered);

}



// ------------------- 槽函数实现 -------------------
void CMenuWidget::onNewActionTriggered()
{
    QMessageBox::information(this, "提示", "你点击了新建菜单");
}

void CMenuWidget::onOpenActionTriggered()
{
    emit toTestVLCKits();
}

void CMenuWidget::onCopyActionTriggered()
{
    QMessageBox::information(this, "提示", "你点击了复制菜单");
}

void CMenuWidget::onPasteActionTriggered()
{
    QMessageBox::information(this, "提示", "你点击了粘贴菜单");
}
