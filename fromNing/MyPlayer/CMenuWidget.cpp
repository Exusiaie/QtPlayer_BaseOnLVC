#include "CMenuWidget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QCursor>
#include <QDebug>

CMenuWidget::CMenuWidget(QWidget *parent)
    : QWidget(parent)
{

    // 调用初始化函数
    initMenuBar();
//    initRightMenu();

    // 创建一个垂直布局来容纳菜单栏和右键菜单
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
      _ptestVLCKits = new TestVLCKits(this);
    mainLayout->addWidget(_pmenuBar);
   // mainLayout->addStretch(); // 填充剩余空间，使菜单栏保持在顶部
    mainLayout->setContentsMargins(0,0,0,0);
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
      connect(this, &CMenuWidget::toTestVLCKits, _ptestVLCKits, &TestVLCKits::handlePlay);
    // 使用 QFileDialog::getOpenFileNames 获取多个文件名
      QStringList fileList = QFileDialog::getOpenFileNames(this, "请选择视频文件",
                                                            "C:/Users/18388/Desktop/1. 播放器项目/视频播放器项目资料/videos",
                                                            "视频文件(*.mp4);;视频文件(*.avi);;");
      if (fileList.isEmpty()) {
          return;
      }

//      bool ret = _ptestVLCKits

      // 调用VLCKits的play方法，传入文件名列表和窗口ID
      // 注意：play函数现在接受的是QStringList，而不是单个QString
//      bool ret = _pVLCKits->play(fileList, (void*)ui->videoWidget->winId());
//      if(!ret){
//          qDebug("文件播放失败");
//          return;
//      }

      //Windows头文件中的定时器函数
     // SetTimer(NULL, 1, 300, TimeProc);
}

void CMenuWidget::onCopyActionTriggered()
{
    QMessageBox::information(this, "提示", "你点击了复制菜单");
}

void CMenuWidget::onPasteActionTriggered()
{
    QMessageBox::information(this, "提示", "你点击了粘贴菜单");
}
