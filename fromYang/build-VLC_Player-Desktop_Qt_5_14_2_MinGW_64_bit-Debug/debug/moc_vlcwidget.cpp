/****************************************************************************
** Meta object code from reading C++ file 'vlcwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../VLC_Player/vlcwidget.h"
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
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VLCWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VLCWidget_t qt_meta_stringdata_VLCWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "VLCWidget"
QT_MOC_LITERAL(1, 10, 22), // "set_timer_slider_value"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "value"
QT_MOC_LITERAL(4, 40, 14), // "set_timer_text"
QT_MOC_LITERAL(5, 55, 4), // "text"
QT_MOC_LITERAL(6, 60, 23), // "set_volume_slider_value"
QT_MOC_LITERAL(7, 84, 19), // "hide_central_button"
QT_MOC_LITERAL(8, 104, 18), // "media_list_updated"
QT_MOC_LITERAL(9, 123, 18), // "on_openbtn_clicked"
QT_MOC_LITERAL(10, 142, 18), // "on_playbtn_clicked"
QT_MOC_LITERAL(11, 161, 19), // "on_pausebtn_clicked"
QT_MOC_LITERAL(12, 181, 18), // "on_stopbtn_clicked"
QT_MOC_LITERAL(13, 200, 22), // "on_play_media_by_index"
QT_MOC_LITERAL(14, 223, 5) // "index"

    },
    "VLCWidget\0set_timer_slider_value\0\0"
    "value\0set_timer_text\0text\0"
    "set_volume_slider_value\0hide_central_button\0"
    "media_list_updated\0on_openbtn_clicked\0"
    "on_playbtn_clicked\0on_pausebtn_clicked\0"
    "on_stopbtn_clicked\0on_play_media_by_index\0"
    "index"
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
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,
       7,    0,   73,    2, 0x06 /* Public */,
       8,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   75,    2, 0x0a /* Public */,
      10,    0,   76,    2, 0x0a /* Public */,
      11,    0,   77,    2, 0x0a /* Public */,
      12,    0,   78,    2, 0x0a /* Public */,
      13,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void VLCWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VLCWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_timer_slider_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->set_timer_text((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->set_volume_slider_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->hide_central_button(); break;
        case 4: _t->media_list_updated(); break;
        case 5: _t->on_openbtn_clicked(); break;
        case 6: _t->on_playbtn_clicked(); break;
        case 7: _t->on_pausebtn_clicked(); break;
        case 8: _t->on_stopbtn_clicked(); break;
        case 9: _t->on_play_media_by_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VLCWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCWidget::set_timer_slider_value)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VLCWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCWidget::set_timer_text)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VLCWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCWidget::set_volume_slider_value)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VLCWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCWidget::hide_central_button)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VLCWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCWidget::media_list_updated)) {
                *result = 4;
                return;
            }
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

// SIGNAL 0
void VLCWidget::set_timer_slider_value(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VLCWidget::set_timer_text(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VLCWidget::set_volume_slider_value(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VLCWidget::hide_central_button()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void VLCWidget::media_list_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
