/****************************************************************************
** Meta object code from reading C++ file 'SceneViewport.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SceneViewport.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SceneViewport.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_SceneViewport_t {};
static constexpr auto qt_meta_stringdata_SceneViewport = QtMocHelpers::stringData(
    "SceneViewport",
    "ViewportReady",
    "",
    "LoadResources",
    "RenderScene"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_SceneViewport_t {
    uint offsetsAndSizes[10];
    char stringdata0[14];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SceneViewport_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SceneViewport_t qt_meta_stringdata_SceneViewport = {
    {
        QT_MOC_LITERAL(0, 13),  // "SceneViewport"
        QT_MOC_LITERAL(14, 13),  // "ViewportReady"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 13),  // "LoadResources"
        QT_MOC_LITERAL(43, 11)   // "RenderScene"
    },
    "SceneViewport",
    "ViewportReady",
    "",
    "LoadResources",
    "RenderScene"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SceneViewport[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   33,    2, 0x08,    2 /* Private */,
       4,    0,   34,    2, 0x08,    3 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SceneViewport::staticMetaObject = { {
    QMetaObject::SuperData::link<QDirect3D12Widget::staticMetaObject>(),
    qt_meta_stringdata_SceneViewport.offsetsAndSizes,
    qt_meta_data_SceneViewport,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SceneViewport_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SceneViewport, std::true_type>,
        // method 'ViewportReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LoadResources'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'RenderScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SceneViewport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SceneViewport *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ViewportReady(); break;
        case 1: _t->LoadResources(); break;
        case 2: _t->RenderScene(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SceneViewport::*)();
            if (_t _q_method = &SceneViewport::ViewportReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *SceneViewport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SceneViewport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SceneViewport.stringdata0))
        return static_cast<void*>(this);
    return QDirect3D12Widget::qt_metacast(_clname);
}

int SceneViewport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDirect3D12Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SceneViewport::ViewportReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
