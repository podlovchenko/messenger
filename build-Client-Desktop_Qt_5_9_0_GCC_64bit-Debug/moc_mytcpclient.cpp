/****************************************************************************
** Meta object code from reading C++ file 'mytcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/mytcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyTcpClient_t {
    QByteArrayData data[21];
    char stringdata0[228];
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
QT_MOC_LITERAL(11, 129, 3), // "end"
QT_MOC_LITERAL(12, 133, 8), // "slotRead"
QT_MOC_LITERAL(13, 142, 10), // "sendString"
QT_MOC_LITERAL(14, 153, 12), // "verification"
QT_MOC_LITERAL(15, 166, 4), // "name"
QT_MOC_LITERAL(16, 171, 8), // "sendFile"
QT_MOC_LITERAL(17, 180, 15), // "getInterlocutor"
QT_MOC_LITERAL(18, 196, 7), // "getName"
QT_MOC_LITERAL(19, 204, 15), // "setInterlocutor"
QT_MOC_LITERAL(20, 220, 7) // "setName"

    },
    "MyTcpClient\0messageRecieve\0\0message\0"
    "flag\0newClientConnected\0client\0"
    "clientDisconnected\0currentInterlocutor\0"
    "interlocutor\0clearChat\0end\0slotRead\0"
    "sendString\0verification\0name\0sendFile\0"
    "getInterlocutor\0getName\0setInterlocutor\0"
    "setName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       5,    1,   89,    2, 0x06 /* Public */,
       7,    1,   92,    2, 0x06 /* Public */,
       8,    1,   95,    2, 0x06 /* Public */,
      10,    0,   98,    2, 0x06 /* Public */,
      11,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  100,    2, 0x0a /* Public */,
      13,    2,  101,    2, 0x0a /* Public */,
      14,    1,  106,    2, 0x0a /* Public */,
      16,    1,  109,    2, 0x0a /* Public */,
      17,    0,  112,    2, 0x0a /* Public */,
      18,    0,  113,    2, 0x0a /* Public */,
      19,    1,  114,    2, 0x0a /* Public */,
      20,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Bool, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

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
        case 5: _t->end(); break;
        case 6: _t->slotRead(); break;
        case 7: _t->sendString((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: { bool _r = _t->verification((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->sendFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: { QString _r = _t->getInterlocutor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setInterlocutor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyTcpClient::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::messageRecieve)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::newClientConnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::clientDisconnected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::currentInterlocutor)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::clearChat)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MyTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpClient::end)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MyTcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyTcpClient.data,
      qt_meta_data_MyTcpClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MyTcpClient::messageRecieve(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyTcpClient::newClientConnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyTcpClient::clientDisconnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyTcpClient::currentInterlocutor(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyTcpClient::clearChat()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MyTcpClient::end()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
