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
private:
    QSlider * _pslider = nullptr;
};
#endif // CVOLUMESLIDERDIALOG_H

