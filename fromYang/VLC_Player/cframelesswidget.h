#ifndef CFRAMELESSWIDGET_H
#define CFRAMELESSWIDGET_H

#include <QWidget>

class CFramelessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CFramelessWidget(QWidget *parent = nullptr);

signals:

};

#endif // CFRAMELESSWIDGET_H
