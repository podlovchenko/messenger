/****************************************************************************
** Meta object code from reading C++ file 'mytcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/mytcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyTcpClient_t {
    QByteArrayData data[18];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTcpClient_t qt_meta_stringdata_MyTcpClient = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTcpClient"
QT_MOC_LITERAL(1, 12, 14), // "messageRecieve"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "message"
QT_MOC_LITERAL(4, 36, 4), // "flag"
QT_MOC_LITERAL(5, 41, 18), // "newClientConnected"
QT_MOC_LITERAL(6, 60, 6), // "client"
QT_MOC_LITERAL(7, 67, 18), // "clientDisconnected"
QT_MOC_LITERAL(8, 86, 19), // "currentInterlocutor"
QT_MOC_LITERAL(9, 106, 12), // "interlocutor"
QT_MOC_LITERAL(10, 119, 9), // "clearChat"
QT_MOC_LITERAL(11, 129, 8), // "slotRead"
QT_MOC_LITERAL(12, 138, 10), // "sendString"
QT_MOC_LITERAL(13, 149, 7), // "setName"
QT_MOC_LITERAL(14, 157, 15), // "getInterlocutor"
QT_MOC_LITERAL(15, 173, 15), // "setInterlocutor"
QT_MOC_LITERAL(16, 189, 12), // "verification"
QT_MOC_LITERAL(17, 202, 4) // "name"

    },
    "MyTcpClient\0messageRecieve\0\0message\0"
    "flag\0newClientConnected\0client\0"
    "clientDisconnected\0currentInterlocutor\0"
    "interlocutor\0clearChat\0slotRead\0"
    "sendString\0setName\0getInterlocutor\0"
    "setInterlocutor\0verification\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       5,    1,   74,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,
       8,    1,   80,    2, 0x06 /* Public */,
      10,    0,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   84,    2, 0x0a /* Public */,
      12,    2,   85,    2, 0x0a /* Public */,
      13,    1,   90,    2, 0x0a /* Public */,
      14,    0,   93,    2, 0x0a /* Public */,
      15,    1,   94,    2, 0x0a /* Public */,
      16,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Bool, QMetaType::QString,   17,

       0        // eod
};

void MyTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyTcpClient *_t = static_cast<MyTcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageRecieve((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->newClientConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->clientDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->currentInterlocutor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->clearChat(); break;
        case 5: _t->slotRead(); break;
        case 6: _t->sendString((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: { QString _r = _t->getInterlocutor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: _t->setInterlocutor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: { bool _r = _t->verification((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyTcpClient::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::messageRecieve)) {
                *result = 0;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::newClientConnected)) {
                *result = 1;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::clientDisconnected)) {
                *result = 2;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::currentInterlocutor)) {
                *result = 3;
            }
        }
        {
            typedef void (MyTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::clearChat)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject MyTcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyTcpClient.data,
      qt_meta_data_MyTcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpClient.stringdata0))
        return static_cast<void*>(const_cast< MyTcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int MyTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MyTcpClient::messageRecieve(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyTcpClient::newClientConnected(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyTcpClient::clientDisconnected(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyTcpClient::currentInterlocutor(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyTcpClient::clearChat()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
