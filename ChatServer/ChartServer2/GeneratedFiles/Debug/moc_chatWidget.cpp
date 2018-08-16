/****************************************************************************
** Meta object code from reading C++ file 'chatWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../chatWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_chatWidget_t {
    QByteArrayData data[21];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_chatWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_chatWidget_t qt_meta_stringdata_chatWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "chatWidget"
QT_MOC_LITERAL(1, 11, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 18), // "on_sendBtn_clicked"
QT_MOC_LITERAL(4, 55, 11), // "getFileName"
QT_MOC_LITERAL(5, 67, 29), // "on_fontCbx_currentFontChanged"
QT_MOC_LITERAL(6, 97, 1), // "f"
QT_MOC_LITERAL(7, 99, 30), // "on_sizeCbx_currentIndexChanged"
QT_MOC_LITERAL(8, 130, 4), // "arg1"
QT_MOC_LITERAL(9, 135, 19), // "on_boldTBtn_clicked"
QT_MOC_LITERAL(10, 155, 7), // "checked"
QT_MOC_LITERAL(11, 163, 21), // "on_italicTBtn_clicked"
QT_MOC_LITERAL(12, 185, 24), // "on_underlineTBtn_clicked"
QT_MOC_LITERAL(13, 210, 20), // "on_colorTBtn_clicked"
QT_MOC_LITERAL(14, 231, 13), // "curFmtChanged"
QT_MOC_LITERAL(15, 245, 15), // "QTextCharFormat"
QT_MOC_LITERAL(16, 261, 3), // "fmt"
QT_MOC_LITERAL(17, 265, 19), // "on_saveTBtn_clicked"
QT_MOC_LITERAL(18, 285, 20), // "on_clearTBtn_clicked"
QT_MOC_LITERAL(19, 306, 18), // "on_exitBtn_clicked"
QT_MOC_LITERAL(20, 325, 19) // "on_sendTBtn_clicked"

    },
    "chatWidget\0processPendingDatagrams\0\0"
    "on_sendBtn_clicked\0getFileName\0"
    "on_fontCbx_currentFontChanged\0f\0"
    "on_sizeCbx_currentIndexChanged\0arg1\0"
    "on_boldTBtn_clicked\0checked\0"
    "on_italicTBtn_clicked\0on_underlineTBtn_clicked\0"
    "on_colorTBtn_clicked\0curFmtChanged\0"
    "QTextCharFormat\0fmt\0on_saveTBtn_clicked\0"
    "on_clearTBtn_clicked\0on_exitBtn_clicked\0"
    "on_sendTBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chatWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       5,    1,   89,    2, 0x08 /* Private */,
       7,    1,   92,    2, 0x08 /* Private */,
       9,    1,   95,    2, 0x08 /* Private */,
      11,    1,   98,    2, 0x08 /* Private */,
      12,    1,  101,    2, 0x08 /* Private */,
      13,    0,  104,    2, 0x08 /* Private */,
      14,    1,  105,    2, 0x08 /* Private */,
      17,    1,  108,    2, 0x08 /* Private */,
      18,    1,  111,    2, 0x08 /* Private */,
      19,    1,  114,    2, 0x08 /* Private */,
      20,    1,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QFont,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,

       0        // eod
};

void chatWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        chatWidget *_t = static_cast<chatWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processPendingDatagrams(); break;
        case 1: _t->on_sendBtn_clicked(); break;
        case 2: _t->getFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_fontCbx_currentFontChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 4: _t->on_sizeCbx_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_boldTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_italicTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_underlineTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_colorTBtn_clicked(); break;
        case 9: _t->curFmtChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 10: _t->on_saveTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_clearTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_exitBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_sendTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject chatWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_chatWidget.data,
      qt_meta_data_chatWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *chatWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_chatWidget.stringdata0))
        return static_cast<void*>(const_cast< chatWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int chatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
