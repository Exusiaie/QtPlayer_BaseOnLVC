/****************************************************************************
** Meta object code from reading C++ file 'CVideoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MyPlayer/CVideoWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CVideoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CVideoWidget_t {
    QByteArrayData data[15];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVideoWidget_t qt_meta_stringdata_CVideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CVideoWidget"
QT_MOC_LITERAL(1, 13, 15), // "sig_playsstatus"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "playstatus"
QT_MOC_LITERAL(4, 41, 14), // "sigTimeChanged"
QT_MOC_LITERAL(5, 56, 7), // "current"
QT_MOC_LITERAL(6, 64, 5), // "total"
QT_MOC_LITERAL(7, 70, 18), // "on_btnOpen_clicked"
QT_MOC_LITERAL(8, 89, 20), // "on_btnPlayer_clicked"
QT_MOC_LITERAL(9, 110, 19), // "on_btnPause_clicked"
QT_MOC_LITERAL(10, 130, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(11, 149, 25), // "on_playSlider_sliderMoved"
QT_MOC_LITERAL(12, 175, 8), // "position"
QT_MOC_LITERAL(13, 184, 27), // "on_volumeSlider_sliderMoved"
QT_MOC_LITERAL(14, 212, 24) // "on_btnFullScreen_clicked"

    },
    "CVideoWidget\0sig_playsstatus\0\0playstatus\0"
    "sigTimeChanged\0current\0total\0"
    "on_btnOpen_clicked\0on_btnPlayer_clicked\0"
    "on_btnPause_clicked\0on_btnStop_clicked\0"
    "on_playSlider_sliderMoved\0position\0"
    "on_volumeSlider_sliderMoved\0"
    "on_btnFullScreen_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVideoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   67,    2, 0x0a /* Public */,
       8,    0,   68,    2, 0x0a /* Public */,
       9,    0,   69,    2, 0x0a /* Public */,
      10,    0,   70,    2, 0x0a /* Public */,
      11,    1,   71,    2, 0x0a /* Public */,
      13,    1,   74,    2, 0x0a /* Public */,
      14,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,

       0        // eod
};

void CVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CVideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_playsstatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigTimeChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->on_btnOpen_clicked(); break;
        case 3: _t->on_btnPlayer_clicked(); break;
        case 4: _t->on_btnPause_clicked(); break;
        case 5: _t->on_btnStop_clicked(); break;
        case 6: _t->on_playSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_volumeSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_btnFullScreen_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CVideoWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoWidget::sig_playsstatus)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CVideoWidget::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoWidget::sigTimeChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CVideoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CVideoWidget.data,
    qt_meta_data_CVideoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CVideoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CVideoWidget::sig_playsstatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CVideoWidget::sigTimeChanged(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
