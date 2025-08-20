#ifndef CVOLUMESLIDERDIALOG_H
#define CVOLUMESLIDERDIALOG_H
#include <QDialog>
#include <QSlider>
class CVolumeSliderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CVolumeSliderDialog(QWidget * parent = Q_NULLPTR);
    ~CVolumeSliderDialog();

    int value();               // 获取当前音量值 (0~100)
    void setSliderValue(int value);  // 设置音量值 (0~100)

signals:
    void sliderValueChanged(int value);

private:
    QSlider * _pslider = nullptr;
    int temp; // 保存音量值
};
#endif // CVOLUMESLIDERDIALOG_H

