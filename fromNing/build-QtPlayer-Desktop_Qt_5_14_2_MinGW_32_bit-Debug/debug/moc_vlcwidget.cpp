/****************************************************************************
** Meta object code from reading C++ file 'vlcwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtPlayer/vlcwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vlcwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VLCWidget_t {
    QByteArrayData data[15];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VLCWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VLCWidget_t qt_meta_stringdata_VLCWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "VLCWidget"
QT_MOC_LITERAL(1, 10, 18), // "on_btnOpen_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "on_btnPlayer_clicked"
QT_MOC_LITERAL(4, 51, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(5, 71, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(6, 90, 25), // "on_playSlider_sliderMoved"
QT_MOC_LITERAL(7, 116, 8), // "position"
QT_MOC_LITERAL(8, 125, 27), // "on_volumeSlider_sliderMoved"
QT_MOC_LITERAL(9, 153, 19), // "on_sigTimeSliderPos"
QT_MOC_LITERAL(10, 173, 5), // "value"
QT_MOC_LITERAL(11, 179, 14), // "on_sigTimeText"
QT_MOC_LITERAL(12, 194, 3), // "str"
QT_MOC_LITERAL(13, 198, 21), // "on_sigVolumeSliderPos"
QT_MOC_LITERAL(14, 220, 24) // "on_btnFullScreen_clicked"

    },
    "VLCWidget\0on_btnOpen_clicked\0\0"
    "on_btnPlayer_clicked\0on_btnPause_clicked\0"
    "on_btnStop_clicked\0on_playSlider_sliderMoved\0"
    "position\0on_volumeSlider_sliderMoved\0"
    "on_sigTimeSliderPos\0value\0on_sigTimeText\0"
    "str\0on_sigVolumeSliderPos\0"
    "on_btnFullScreen_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VLCWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    1,   68,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
       9,    1,   74,    2, 0x08 /* Private */,
      11,    1,   77,    2, 0x08 /* Private */,
      13,    1,   80,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void VLCWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VLCWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnOpen_clicked(); break;
        case 1: _t->on_btnPlayer_clicked(); break;
        case 2: _t->on_btnPause_clicked(); break;
        case 3: _t->on_btnStop_clicked(); break;
        case 4: _t->on_playSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_volumeSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_sigTimeSliderPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_sigTimeText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_sigVolumeSliderPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_btnFullScreen_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VLCWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VLCWidget.data,
    qt_meta_data_VLCWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VLCWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VLCWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VLCWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VLCWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
