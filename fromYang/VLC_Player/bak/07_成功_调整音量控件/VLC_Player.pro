QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cframelesswidget.cpp \
    cmainwindow.cpp \
    ctitlebar.cpp \
    cvolumebutton.cpp \
    cvolumedialog.cpp \
    main.cpp \
    vlcwidget.cpp \
    widget.cpp

HEADERS += \
    cframelesswidget.h \
    cmainwindow.h \
    ctitlebar.h \
    cvolumebutton.h \
    cvolumedialog.h \
    qss.h \
    vlcwidget.h \
    widget.h

FORMS += \
    widget.ui

INCLUDEPATH += ./vlc-3.0.18-win64/sdk/include
LIBS += $$PWD/vlc-3.0.18-win64/sdk/lib/libvlc.lib
LIBS += $$PWD/vlc-3.0.18-win64/sdk/lib/libvlccore.lib
#LIBS += $$PWD/windows-kits/Ole32.Lib  # 添加这行以链接ole32库，注意需要把windows Kits下的Lib搬到当前目录下
win32:LIBS += -lole32

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/audio_mute.svg \
    resources/audio_open.svg \
    resources/audio_open.svg.svg \
    resources/audio_open_hover.svg.svg \
    resources/down_arrow.svg \
    resources/exit.png \
    resources/file.png \
    resources/play.png \
    resources/set.png \
    resources/titlebar/close.svg \
    resources/titlebar/max.svg \
    resources/titlebar/menu.svg \
    resources/titlebar/min.svg \
    resources/titlebar/min_bak.svg \
    resources/titlebar/normal.svg \
    resources/titlebar/set.svg \
    resources/titlebar/title_icon.png \
    resources/tools.png \
    resources/up_arrow.svg
