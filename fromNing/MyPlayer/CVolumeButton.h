#ifndef CVOLUMEBUTTON_H
#define CVOLUMEBUTTON_H

#include "CVolumeSliderDialog.h"
#include <QPushButton>
class CVolumeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CVolumeButton(QWidget *parent = nullptr);
    ~CVolumeButton();
signals:
protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent *event) override;
    void hide();
private:
    CVolumeSliderDialog * _pvolumeSliderDlg;
};

#endif // CVOLUMEBUTTON_H
