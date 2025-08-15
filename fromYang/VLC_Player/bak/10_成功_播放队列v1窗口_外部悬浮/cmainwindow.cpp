#include "cmainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

CMainWindow::CMainWindow(QWidget * parent)
    : CFramelessWidget(parent)
{
    initUI();
}

void CMainWindow::closeSlot()
{
    QMessageBox::StandardButton isExit = QMessageBox::warning(this, "提示",
                                                              "你确定要退出吗？",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(isExit == QMessageBox::Yes) {
        close();
    }
}

void CMainWindow::initUI()
{
    _ptitleBar = new CTitleBar(this);

    QWidget * wbody = new QWidget(this);
    wbody->setMinimumSize(800, 600);

    QVBoxLayout * pvLayout = new QVBoxLayout(this);
    pvLayout->addWidget(_ptitleBar);
    pvLayout->addWidget(wbody);
    pvLayout->setContentsMargins(0, 0, 0, 0);
//    connect(_ptitleBar, &CTitleBar::sigClose, this, &CMainWindow::closeSlot);
}
