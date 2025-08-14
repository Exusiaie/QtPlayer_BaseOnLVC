#ifndef CMENUWIDGET_H
#define CMENUWIDGET_H

#include "TestVLCKits.h"

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <windows.h>

class CMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CMenuWidget(QWidget *parent = nullptr);
    ~CMenuWidget();

private slots:
    void onNewActionTriggered();
    void onOpenActionTriggered();
    void onCopyActionTriggered();
    void onPasteActionTriggered();
signals:
    void toTestVLCKits();

private:
    void initMenuBar();
    void initRightMenu();

private:
    QMenuBar *_pmenuBar; // 菜单栏

    TestVLCKits *_ptestVLCKits;

};

#endif // CMENUWIDGET_H
