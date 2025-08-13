#include "CFramelessWidget.h"
#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>
#include <QDebug>

CFramelessWidget::CFramelessWidget(QWidget *parent)
    : QWidget(parent)
{
    // 参数(无边框标题栏 | 保留最大最小按钮)
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    // 接收悬停(Hover)事件
    setAttribute(Qt::WA_Hover);
}

CFramelessWidget::~CFramelessWidget()
{}


#if 1
bool CFramelessWidget::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    MSG* param = static_cast<MSG*>(message);    // 一个指向 MSG 结构体的指针，这个结构体包含了 Windows 消息的所有信息，包括消息类型 message 和鼠标坐标 lParam。

    switch (param->message)
    {
    case WM_NCHITTEST:  // 当鼠标在非客户区域将返回值告诉系统鼠标的位置
    {

        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();
        qDebug() << "X_LPARAM:" << GET_X_LPARAM(param->lParam);
        qDebug() << "Y_LPARAM:" << GET_Y_LPARAM(param->lParam);
        qDebug() << "geometry.x: " << geometry().x();
        qDebug() << "geometry.y: " << geometry().y();
        qDebug() << "nX:" << nX << ", nY:" << nY;
        qDebug() << "this->width():" << this->width();
        qDebug() << "this->height():" << this->height();

        if (nX > m_nBorderWidth && nX < this->width() - m_nBorderWidth &&
            nY > m_nBorderWidth && nY < this->height() - m_nBorderWidth)
        {
            if (childAt(nX, nY) != nullptr) // 鼠标不在任何边界区就在窗口内部
                //调用基类的同名虚函数，继续处理事件
                return QWidget::nativeEvent(eventType, message, result);
        }

        if ((nX > 0) && (nX < m_nBorderWidth))  // 鼠标在窗口左侧
            *result = HTLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width()))
            *result = HTRIGHT;

        if ((nY > 0) && (nY < m_nBorderWidth))
            *result = HTTOP;

        if ((nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOM;

        if ((nX > 0) && (nX < m_nBorderWidth) && (nY > 0)
            && (nY < m_nBorderWidth))
            *result = HTTOPLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
            && (nY > 0) && (nY < m_nBorderWidth))
            *result = HTTOPRIGHT;

        if ((nX > 0) && (nX < m_nBorderWidth)
            && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOMLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
            && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOMRIGHT;

        return true;//不再传递事件
    }//end of case
    }//end of switch
    return false;//传递事件
}

#endif

