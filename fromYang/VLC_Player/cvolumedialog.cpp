#include "cvolumedialog.h"
#include "qss.h"
#include <QVBoxLayout>

CVolumeSliderDialog::CVolumeSliderDialog(QWidget * parent)
    : QDialog(parent)
{
    this->setFixedSize(40, 200);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
//    this->setStyleSheet("QDialog{background-color: rgba(255, 251, 235, 0.9);}");

    _pslider = new QSlider(this);
    _pslider->setOrientation(Qt::Vertical);
    _pslider->setStyleSheet(QString::fromStdString(slider_qss));
//    _pslider->setStyleSheet("QSlider{background-color:transparent;}");  // 会覆盖原来的设置！

    QVBoxLayout * pvlayout = new QVBoxLayout(this);
    pvlayout->addWidget(_pslider);
}
CVolumeSliderDialog::~CVolumeSliderDialog(){}
