/****************************************************************************
** Meta object code from reading C++ file 'qtcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtControl_t {
    QByteArrayData data[13];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtControl_t qt_meta_stringdata_QtControl = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QtControl"
QT_MOC_LITERAL(1, 10, 13), // "coverShowSlot"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "btnClick"
QT_MOC_LITERAL(4, 34, 11), // "getPosClick"
QT_MOC_LITERAL(5, 46, 11), // "transResult"
QT_MOC_LITERAL(6, 58, 17), // "QMap<int,QPointF>"
QT_MOC_LITERAL(7, 76, 13), // "popUpTempUnit"
QT_MOC_LITERAL(8, 90, 13), // "popUpLanguage"
QT_MOC_LITERAL(9, 104, 13), // "resetLanguage"
QT_MOC_LITERAL(10, 118, 16), // "tempUnitSelected"
QT_MOC_LITERAL(11, 135, 4), // "data"
QT_MOC_LITERAL(12, 140, 16) // "languageSelected"

    },
    "QtControl\0coverShowSlot\0\0btnClick\0"
    "getPosClick\0transResult\0QMap<int,QPointF>\0"
    "popUpTempUnit\0popUpLanguage\0resetLanguage\0"
    "tempUnitSelected\0data\0languageSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    1,   68,    2, 0x08 /* Private */,
      12,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   11,
    QMetaType::Void, QMetaType::QStringList,   11,

       0        // eod
};

void QtControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtControl *_t = static_cast<QtControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->coverShowSlot(); break;
        case 1: _t->btnClick(); break;
        case 2: _t->getPosClick(); break;
        case 3: _t->transResult((*reinterpret_cast< QMap<int,QPointF>(*)>(_a[1]))); break;
        case 4: _t->popUpTempUnit(); break;
        case 5: _t->popUpLanguage(); break;
        case 6: _t->resetLanguage(); break;
        case 7: _t->tempUnitSelected((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->languageSelected((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QtControl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtControl.data,
      qt_meta_data_QtControl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtControl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtControl.stringdata0))
        return static_cast<void*>(const_cast< QtControl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
