#include "CVolumeSliderDialog.h"
#include <QVBoxLayout>
#include <QDebug>

CVolumeSliderDialog::CVolumeSliderDialog(QWidget * parent)
    : QDialog(parent)
{
    this->setFixedSize(60, 200);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    this->setStyleSheet("QDialog{background-color: rgba(54,54,54, 0.5)}");
    _pslider = new QSlider(this);
    _pslider->setOrientation(Qt::Vertical);
    _pslider->setValue(100);
    //_pslider->setStyleSheet("QSlider{background-color:rgba(255,0,0,0.5)}");
    QVBoxLayout * pvlayout = new QVBoxLayout(this);
    pvlayout->addWidget(_pslider);

    // 控制音量的信号就是从这里发出去的, 世界起源
    connect(_pslider, &QSlider::valueChanged, this, &CVolumeSliderDialog::sliderValueChanged);

}

CVolumeSliderDialog::~CVolumeSliderDialog(){}

int CVolumeSliderDialog::value()
{

    temp = (_pslider ? _pslider->value() : 0);
    qDebug() << "当前声音值" << temp;
    return temp;

}

void CVolumeSliderDialog::setSliderValue(int value)
{
    if (_pslider) {
        _pslider->setValue(value);
        qDebug() << "value: "  << value;
    }
}

