/****************************************************************************
** Meta object code from reading C++ file 'cbuttombar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../VLC_Player/cbuttombar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cbuttombar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CButtomBar_t {
    QByteArrayData data[13];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CButtomBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CButtomBar_t qt_meta_stringdata_CButtomBar = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CButtomBar"
QT_MOC_LITERAL(1, 11, 17), // "openButtonClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "playButtonClicked"
QT_MOC_LITERAL(4, 48, 18), // "pauseButtonClicked"
QT_MOC_LITERAL(5, 67, 17), // "stopButtonClicked"
QT_MOC_LITERAL(6, 85, 15), // "timeSliderMoved"
QT_MOC_LITERAL(7, 101, 5), // "value"
QT_MOC_LITERAL(8, 107, 19), // "onOpenButtonClicked"
QT_MOC_LITERAL(9, 127, 19), // "onPlayButtonClicked"
QT_MOC_LITERAL(10, 147, 20), // "onPauseButtonClicked"
QT_MOC_LITERAL(11, 168, 19), // "onStopButtonClicked"
QT_MOC_LITERAL(12, 188, 17) // "onTimeSliderMoved"

    },
    "CButtomBar\0openButtonClicked\0\0"
    "playButtonClicked\0pauseButtonClicked\0"
    "stopButtonClicked\0timeSliderMoved\0"
    "value\0onOpenButtonClicked\0onPlayButtonClicked\0"
    "onPauseButtonClicked\0onStopButtonClicked\0"
    "onTimeSliderMoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CButtomBar[] = {

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
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void CButtomBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CButtomBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openButtonClicked(); break;
        case 1: _t->playButtonClicked(); break;
        case 2: _t->pauseButtonClicked(); break;
        case 3: _t->stopButtonClicked(); break;
        case 4: _t->timeSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onOpenButtonClicked(); break;
        case 6: _t->onPlayButtonClicked(); break;
        case 7: _t->onPauseButtonClicked(); break;
        case 8: _t->onStopButtonClicked(); break;
        case 9: _t->onTimeSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CButtomBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CButtomBar::openButtonClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CButtomBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CButtomBar::playButtonClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CButtomBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CButtomBar::pauseButtonClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CButtomBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CButtomBar::stopButtonClicked)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CButtomBar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CButtomBar::timeSliderMoved)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CButtomBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CButtomBar.data,
    qt_meta_data_CButtomBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CButtomBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CButtomBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CButtomBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CButtomBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CButtomBar::openButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CButtomBar::playButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CButtomBar::pauseButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CButtomBar::stopButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CButtomBar::timeSliderMoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
