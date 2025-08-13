#ifndef CTITLEBAR_H
#define CTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class CTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CTitleBar(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent * event) override;

signals:
    void sigClose();

private:
    void initUI();

private slots:
    void onClickedSlot();

private:
    QLabel * _plogoLabel;
    QLabel * _ptitleTextLabel;
    QPushButton * _psetButton;
    QPushButton * _pminButton;
    QPushButton * _pmaxButton;
    QPushButton * _pcloseButton;

};

#endif // CTITLEBAR_H
