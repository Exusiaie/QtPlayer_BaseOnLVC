/****************************************************************************
** Meta object code from reading C++ file 'VLCKits.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MyPlayer/VLCKits.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VLCKits.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VLCKits_t {
    QByteArrayData data[11];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VLCKits_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VLCKits_t qt_meta_stringdata_VLCKits = {
    {
QT_MOC_LITERAL(0, 0, 7), // "VLCKits"
QT_MOC_LITERAL(1, 8, 16), // "sigTimeSliderPos"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "value"
QT_MOC_LITERAL(4, 32, 11), // "sigTimeText"
QT_MOC_LITERAL(5, 44, 3), // "str"
QT_MOC_LITERAL(6, 48, 18), // "sigVolumeSliderPos"
QT_MOC_LITERAL(7, 67, 14), // "sigTimeChanged"
QT_MOC_LITERAL(8, 82, 7), // "current"
QT_MOC_LITERAL(9, 90, 5), // "total"
QT_MOC_LITERAL(10, 96, 10) // "updateTime"

    },
    "VLCKits\0sigTimeSliderPos\0\0value\0"
    "sigTimeText\0str\0sigVolumeSliderPos\0"
    "sigTimeChanged\0current\0total\0updateTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VLCKits[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       7,    2,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    8,    9,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void VLCKits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VLCKits *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigTimeSliderPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sigTimeText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sigVolumeSliderPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sigTimeChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->updateTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VLCKits::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCKits::sigTimeSliderPos)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VLCKits::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCKits::sigTimeText)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VLCKits::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCKits::sigVolumeSliderPos)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VLCKits::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VLCKits::sigTimeChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VLCKits::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_VLCKits.data,
    qt_meta_data_VLCKits,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VLCKits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VLCKits::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VLCKits.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VLCKits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VLCKits::sigTimeSliderPos(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VLCKits::sigTimeText(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VLCKits::sigVolumeSliderPos(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VLCKits::sigTimeChanged(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
