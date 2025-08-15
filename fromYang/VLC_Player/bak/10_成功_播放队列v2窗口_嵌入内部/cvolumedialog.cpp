#include "cvolumedialog.h"
#include <QVBoxLayout>

CVolumeSliderDialog::CVolumeSliderDialog(QWidget * parent)
    : QDialog(parent)
{
    this->setFixedSize(40, 200);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    this->setStyleSheet("QDialog{background-color: rgba(54, 54, 54, 0.5)}");

    _pslider = new QSlider(this);
    _pslider->setOrientation(Qt::Vertical);
    //_pslider->setStyleSheet("QSlider{background-color:rgba(255, 0, 0, 0.5)}");

    QVBoxLayout * pvlayout = new QVBoxLayout(this);
    pvlayout->addWidget(_pslider);
}
CVolumeSliderDialog::~CVolumeSliderDialog(){}
