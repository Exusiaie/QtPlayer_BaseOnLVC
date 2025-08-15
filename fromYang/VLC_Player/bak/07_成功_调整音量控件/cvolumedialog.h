#ifndef CVOLUMEDIALOG_H
#define CVOLUMEDIALOG_H

#include <QDialog>
#include <QSlider>
class CVolumeSliderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CVolumeSliderDialog(QWidget * parent = Q_NULLPTR);
    ~CVolumeSliderDialog();

    QSlider* getSlider(void) { return _pslider; }
    int getSlierValue(void) { return _pslider->value(); }
    void setSliderValue(int value) { _pslider->setValue(value); }

signals:
    void valueChanged(int value);  // 滑块值变化信号

private:
    QSlider * _pslider = nullptr;

};

#endif // CVOLUMEDIALOG_H
