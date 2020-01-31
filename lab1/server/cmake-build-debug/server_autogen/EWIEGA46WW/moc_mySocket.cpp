/****************************************************************************
** Meta object code from reading C++ file 'mySocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mySocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mySocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mySocket_t {
    QByteArrayData data[5];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mySocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mySocket_t qt_meta_stringdata_mySocket = {
    {
QT_MOC_LITERAL(0, 0, 8), // "mySocket"
QT_MOC_LITERAL(1, 9, 3), // "err"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 6), // "string"
QT_MOC_LITERAL(4, 21, 3) // "log"

    },
    "mySocket\0err\0\0string\0log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mySocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void mySocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mySocket *_t = static_cast<mySocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->err((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 1: _t->err((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->log((*reinterpret_cast< string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mySocket::*_t)(int , string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mySocket::err)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mySocket::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mySocket::err)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (mySocket::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mySocket::log)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject mySocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mySocket.data,
      qt_meta_data_mySocket,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mySocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mySocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mySocket.stringdata0))
        return static_cast<void*>(const_cast< mySocket*>(this));
    return QObject::qt_metacast(_clname);
}

int mySocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void mySocket::err(int _t1, string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mySocket::err(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mySocket::log(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
