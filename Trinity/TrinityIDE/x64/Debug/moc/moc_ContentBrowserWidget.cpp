/****************************************************************************
** Meta object code from reading C++ file 'ContentBrowserWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ContentBrowserWidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContentBrowserWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ContentBrowserWidget_t {
    uint offsetsAndSizes[12];
    char stringdata0[21];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[16];
    char stringdata5[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ContentBrowserWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ContentBrowserWidget_t qt_meta_stringdata_ContentBrowserWidget = {
    {
        QT_MOC_LITERAL(0, 20),  // "ContentBrowserWidget"
        QT_MOC_LITERAL(21, 12),  // "updateWidget"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 8),  // "newValue"
        QT_MOC_LITERAL(44, 15),  // "showContextMenu"
        QT_MOC_LITERAL(60, 3)   // "pos"
    },
    "ContentBrowserWidget",
    "updateWidget",
    "",
    "newValue",
    "showContextMenu",
    "pos"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ContentBrowserWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x0a,    1 /* Public */,
       4,    1,   29,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QPoint,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject ContentBrowserWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<ads::CDockWidget::staticMetaObject>(),
    qt_meta_stringdata_ContentBrowserWidget.offsetsAndSizes,
    qt_meta_data_ContentBrowserWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ContentBrowserWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ContentBrowserWidget, std::true_type>,
        // method 'updateWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'showContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>
    >,
    nullptr
} };

void ContentBrowserWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContentBrowserWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateWidget((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->showContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ContentBrowserWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContentBrowserWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ContentBrowserWidget.stringdata0))
        return static_cast<void*>(this);
    return ads::CDockWidget::qt_metacast(_clname);
}

int ContentBrowserWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ads::CDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
