/********************************************************************************
** Form generated from reading UI file 'vlcwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VLCWIDGET_H
#define UI_VLCWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VLCWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *widgetVideo;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOpen;
    QPushButton *btnPlayer;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *VLCWidget)
    {
        if (VLCWidget->objectName().isEmpty())
            VLCWidget->setObjectName(QString::fromUtf8("VLCWidget"));
        VLCWidget->resize(800, 600);
        horizontalLayout_3 = new QHBoxLayout(VLCWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetVideo = new QWidget(VLCWidget);
        widgetVideo->setObjectName(QString::fromUtf8("widgetVideo"));

        verticalLayout->addWidget(widgetVideo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(VLCWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSlider = new QSlider(VLCWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnOpen = new QPushButton(VLCWidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        horizontalLayout_2->addWidget(btnOpen);

        btnPlayer = new QPushButton(VLCWidget);
        btnPlayer->setObjectName(QString::fromUtf8("btnPlayer"));

        horizontalLayout_2->addWidget(btnPlayer);

        btnPause = new QPushButton(VLCWidget);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));

        horizontalLayout_2->addWidget(btnPause);

        btnStop = new QPushButton(VLCWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        horizontalLayout_2->addWidget(btnStop);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(VLCWidget);

        QMetaObject::connectSlotsByName(VLCWidget);
    } // setupUi

    void retranslateUi(QWidget *VLCWidget)
    {
        VLCWidget->setWindowTitle(QCoreApplication::translate("VLCWidget", "VLCWidget", nullptr));
        label->setText(QCoreApplication::translate("VLCWidget", "TextLabel", nullptr));
        btnOpen->setText(QCoreApplication::translate("VLCWidget", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        btnPlayer->setText(QCoreApplication::translate("VLCWidget", "\346\222\255\346\224\276", nullptr));
        btnPause->setText(QCoreApplication::translate("VLCWidget", "\346\232\202\345\201\234", nullptr));
        btnStop->setText(QCoreApplication::translate("VLCWidget", "\345\201\234\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VLCWidget: public Ui_VLCWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VLCWIDGET_H
