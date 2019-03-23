/****************************************************************************
** Meta object code from reading C++ file 'TcpClientSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpClientSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpClientSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpClientSocket_t {
    QByteArrayData data[18];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpClientSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpClientSocket_t qt_meta_stringdata_TcpClientSocket = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TcpClientSocket"
QT_MOC_LITERAL(1, 16, 10), // "doAddGroup"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "groupname"
QT_MOC_LITERAL(4, 38, 14), // "doSendChatData"
QT_MOC_LITERAL(5, 53, 8), // "username"
QT_MOC_LITERAL(6, 62, 7), // "groupid"
QT_MOC_LITERAL(7, 70, 3), // "msg"
QT_MOC_LITERAL(8, 74, 15), // "doSendUserEnter"
QT_MOC_LITERAL(9, 90, 21), // "doSendRefreshUserInfo"
QT_MOC_LITERAL(10, 112, 18), // "doSendFileNameData"
QT_MOC_LITERAL(11, 131, 10), // "serverAddr"
QT_MOC_LITERAL(12, 142, 10), // "clientAddr"
QT_MOC_LITERAL(13, 153, 8), // "fileName"
QT_MOC_LITERAL(14, 162, 12), // "disconnected"
QT_MOC_LITERAL(15, 175, 7), // "qintptr"
QT_MOC_LITERAL(16, 183, 12), // "dataReceived"
QT_MOC_LITERAL(17, 196, 16) // "slotDisconnected"

    },
    "TcpClientSocket\0doAddGroup\0\0groupname\0"
    "doSendChatData\0username\0groupid\0msg\0"
    "doSendUserEnter\0doSendRefreshUserInfo\0"
    "doSendFileNameData\0serverAddr\0clientAddr\0"
    "fileName\0disconnected\0qintptr\0"
    "dataReceived\0slotDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClientSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    3,   57,    2, 0x06 /* Public */,
       8,    1,   64,    2, 0x06 /* Public */,
       9,    0,   67,    2, 0x06 /* Public */,
      10,    3,   68,    2, 0x06 /* Public */,
      14,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,   78,    2, 0x08 /* Private */,
      17,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 15,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpClientSocket *_t = static_cast<TcpClientSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doAddGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->doSendChatData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->doSendUserEnter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->doSendRefreshUserInfo(); break;
        case 4: _t->doSendFileNameData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->disconnected((*reinterpret_cast< qintptr(*)>(_a[1]))); break;
        case 6: _t->dataReceived(); break;
        case 7: _t->slotDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpClientSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::doAddGroup)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::doSendChatData)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::doSendUserEnter)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::doSendRefreshUserInfo)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::doSendFileNameData)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(qintptr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::disconnected)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject TcpClientSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_TcpClientSocket.data,
      qt_meta_data_TcpClientSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClientSocket.stringdata0))
        return static_cast<void*>(const_cast< TcpClientSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int TcpClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
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
void TcpClientSocket::doAddGroup(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpClientSocket::doSendChatData(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpClientSocket::doSendUserEnter(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpClientSocket::doSendRefreshUserInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void TcpClientSocket::doSendFileNameData(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TcpClientSocket::disconnected(qintptr _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
