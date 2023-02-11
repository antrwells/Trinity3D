/****************************************************************************
** Meta object code from reading C++ file 'TrinityIDE.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../TrinityIDE.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrinityIDE.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_TrinityIDE_t {};
static constexpr auto qt_meta_stringdata_TrinityIDE = QtMocHelpers::stringData(
    "TrinityIDE",
    "ViewportReady",
    "",
    "act_move",
    "act_rotate",
    "act_scale",
    "act_LocalSpace",
    "id",
    "saveLayout",
    "loadLayout"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_TrinityIDE_t {
    uint offsetsAndSizes[20];
    char stringdata0[11];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[11];
    char stringdata5[10];
    char stringdata6[15];
    char stringdata7[3];
    char stringdata8[11];
    char stringdata9[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_TrinityIDE_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_TrinityIDE_t qt_meta_stringdata_TrinityIDE = {
    {
        QT_MOC_LITERAL(0, 10),  // "TrinityIDE"
        QT_MOC_LITERAL(11, 13),  // "ViewportReady"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 8),  // "act_move"
        QT_MOC_LITERAL(35, 10),  // "act_rotate"
        QT_MOC_LITERAL(46, 9),  // "act_scale"
        QT_MOC_LITERAL(56, 14),  // "act_LocalSpace"
        QT_MOC_LITERAL(71, 2),  // "id"
        QT_MOC_LITERAL(74, 10),  // "saveLayout"
        QT_MOC_LITERAL(85, 10)   // "loadLayout"
    },
    "TrinityIDE",
    "ViewportReady",
    "",
    "act_move",
    "act_rotate",
    "act_scale",
    "act_LocalSpace",
    "id",
    "saveLayout",
    "loadLayout"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_TrinityIDE[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    1,   60,    2, 0x08,    5 /* Private */,
       8,    0,   63,    2, 0x08,    7 /* Private */,
       9,    0,   64,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TrinityIDE::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_TrinityIDE.offsetsAndSizes,
    qt_meta_data_TrinityIDE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_TrinityIDE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TrinityIDE, std::true_type>,
        // method 'ViewportReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'act_move'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'act_rotate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'act_scale'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'act_LocalSpace'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'saveLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TrinityIDE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrinityIDE *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ViewportReady(); break;
        case 1: _t->act_move(); break;
        case 2: _t->act_rotate(); break;
        case 3: _t->act_scale(); break;
        case 4: _t->act_LocalSpace((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->saveLayout(); break;
        case 6: _t->loadLayout(); break;
        default: ;
        }
    }
}

const QMetaObject *TrinityIDE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrinityIDE::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrinityIDE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TrinityIDE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
