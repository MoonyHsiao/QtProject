/****************************************************************************
** Meta object code from reading C++ file 'FileServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FileServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileServer_t {
    QByteArrayData data[11];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileServer_t qt_meta_stringdata_FileServer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FileServer"
QT_MOC_LITERAL(1, 11, 11), // "sndFileName"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "fileName"
QT_MOC_LITERAL(4, 33, 6), // "sndMsg"
QT_MOC_LITERAL(5, 40, 15), // "updClntProgress"
QT_MOC_LITERAL(6, 56, 8), // "numBytes"
QT_MOC_LITERAL(7, 65, 19), // "on_sOpenBtn_clicked"
QT_MOC_LITERAL(8, 85, 19), // "on_sSendBtn_clicked"
QT_MOC_LITERAL(9, 105, 21), // "on_cCancleBtn_clicked"
QT_MOC_LITERAL(10, 127, 20) // "on_sCloseBtn_clicked"

    },
    "FileServer\0sndFileName\0\0fileName\0"
    "sndMsg\0updClntProgress\0numBytes\0"
    "on_sOpenBtn_clicked\0on_sSendBtn_clicked\0"
    "on_cCancleBtn_clicked\0on_sCloseBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x08 /* Private */,
       5,    1,   53,    2, 0x08 /* Private */,
       7,    0,   56,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FileServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileServer *_t = static_cast<FileServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sndFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sndMsg(); break;
        case 2: _t->updClntProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->on_sOpenBtn_clicked(); break;
        case 4: _t->on_sSendBtn_clicked(); break;
        case 5: _t->on_cCancleBtn_clicked(); break;
        case 6: _t->on_sCloseBtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FileServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileServer::sndFileName)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FileServer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileServer.data,
      qt_meta_data_FileServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileServer.stringdata0))
        return static_cast<void*>(const_cast< FileServer*>(this));
    return QDialog::qt_metacast(_clname);
}

int FileServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FileServer::sndFileName(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
