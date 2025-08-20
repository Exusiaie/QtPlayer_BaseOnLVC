/****************************************************************************
** Meta object code from reading C++ file 'CBottomCtrlBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MyPlayer/CBottomCtrlBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CBottomCtrlBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CBottomCtrlBar_t {
    QByteArrayData data[14];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CBottomCtrlBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CBottomCtrlBar_t qt_meta_stringdata_CBottomCtrlBar = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CBottomCtrlBar"
QT_MOC_LITERAL(1, 15, 8), // "sig_play"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "sig_stop"
QT_MOC_LITERAL(4, 34, 14), // "sig_fullScreen"
QT_MOC_LITERAL(5, 49, 8), // "sig_seek"
QT_MOC_LITERAL(6, 58, 15), // "positionPercent"
QT_MOC_LITERAL(7, 74, 18), // "sliderValueChanged"
QT_MOC_LITERAL(8, 93, 5), // "value"
QT_MOC_LITERAL(9, 99, 8), // "sig_open"
QT_MOC_LITERAL(10, 108, 20), // "setPositionByPercent"
QT_MOC_LITERAL(11, 129, 13), // "onTimeChanged"
QT_MOC_LITERAL(12, 143, 7), // "current"
QT_MOC_LITERAL(13, 151, 5) // "total"

    },
    "CBottomCtrlBar\0sig_play\0\0sig_stop\0"
    "sig_fullScreen\0sig_seek\0positionPercent\0"
    "sliderValueChanged\0value\0sig_open\0"
    "setPositionByPercent\0onTimeChanged\0"
    "current\0total"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CBottomCtrlBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       9,    0,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   64,    2, 0x0a /* Public */,
      11,    2,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   12,   13,

       0        // eod
};

void CBottomCtrlBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CBottomCtrlBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_play(); break;
        case 1: _t->sig_stop(); break;
        case 2: _t->sig_fullScreen(); break;
        case 3: _t->sig_seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_open(); break;
        case 6: _t->setPositionByPercent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onTimeChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CBottomCtrlBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBottomCtrlBar::sig_play)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CBottomCtrlBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBottomCtrlBar::sig_stop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CBottomCtrlBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBottomCtrlBar::sig_fullScreen)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CBottomCtrlBar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBottomCtrlBar::sig_seek)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CBottomCtrlBar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBottomCtrlBar::sliderValueChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CBottomCtrlBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CBottomCtrlBar::sig_open)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CBottomCtrlBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CBottomCtrlBar.data,
    qt_meta_data_CBottomCtrlBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CBottomCtrlBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CBottomCtrlBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CBottomCtrlBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CBottomCtrlBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CBottomCtrlBar::sig_play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CBottomCtrlBar::sig_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CBottomCtrlBar::sig_fullScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CBottomCtrlBar::sig_seek(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CBottomCtrlBar::sliderValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CBottomCtrlBar::sig_open()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
