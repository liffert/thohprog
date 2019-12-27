/****************************************************************************
** Meta object code from reading C++ file 'Lab4g.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Lab4g.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Lab4g.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Lab4g_t {
    QByteArrayData data[12];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lab4g_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lab4g_t qt_meta_stringdata_Lab4g = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Lab4g"
QT_MOC_LITERAL(1, 6, 4), // "kohl"
QT_MOC_LITERAL(2, 11, 0), // ""
QT_MOC_LITERAL(3, 12, 4), // "kohs"
QT_MOC_LITERAL(4, 17, 3), // "tri"
QT_MOC_LITERAL(5, 21, 4), // "rect"
QT_MOC_LITERAL(6, 26, 3), // "pap"
QT_MOC_LITERAL(7, 30, 3), // "man"
QT_MOC_LITERAL(8, 34, 3), // "RtP"
QT_MOC_LITERAL(9, 38, 3), // "RtM"
QT_MOC_LITERAL(10, 42, 5), // "lvlup"
QT_MOC_LITERAL(11, 48, 5) // "lvldw"

    },
    "Lab4g\0kohl\0\0kohs\0tri\0rect\0pap\0man\0RtP\0"
    "RtM\0lvlup\0lvldw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lab4g[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Lab4g::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Lab4g *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->kohl(); break;
        case 1: _t->kohs(); break;
        case 2: _t->tri(); break;
        case 3: _t->rect(); break;
        case 4: _t->pap(); break;
        case 5: _t->man(); break;
        case 6: _t->RtP(); break;
        case 7: _t->RtM(); break;
        case 8: _t->lvlup(); break;
        case 9: _t->lvldw(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Lab4g::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Lab4g.data,
    qt_meta_data_Lab4g,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Lab4g::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lab4g::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Lab4g.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Lab4g::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
