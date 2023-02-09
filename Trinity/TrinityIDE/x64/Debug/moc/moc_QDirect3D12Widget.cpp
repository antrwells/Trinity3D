/****************************************************************************
** Meta object code from reading C++ file 'QDirect3D12Widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QDirect3D12Widget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QDirect3D12Widget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_QDirect3D12Widget_t {};
static constexpr auto qt_meta_stringdata_QDirect3D12Widget = QtMocHelpers::stringData(
    "QDirect3D12Widget",
    "LoadResources",
    "",
    "deviceInitialized",
    "success",
    "eventHandled",
    "widgetResized",
    "ticked",
    "rendered",
    "ID3D12GraphicsCommandList*",
    "cl",
    "keyPressed",
    "QKeyEvent*",
    "mouseMoved",
    "QMouseEvent*",
    "mouseClicked",
    "mouseReleased",
    "onFrame",
    "onReset"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_QDirect3D12Widget_t {
    uint offsetsAndSizes[38];
    char stringdata0[18];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[8];
    char stringdata5[13];
    char stringdata6[14];
    char stringdata7[7];
    char stringdata8[9];
    char stringdata9[27];
    char stringdata10[3];
    char stringdata11[11];
    char stringdata12[11];
    char stringdata13[11];
    char stringdata14[13];
    char stringdata15[13];
    char stringdata16[14];
    char stringdata17[8];
    char stringdata18[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QDirect3D12Widget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QDirect3D12Widget_t qt_meta_stringdata_QDirect3D12Widget = {
    {
        QT_MOC_LITERAL(0, 17),  // "QDirect3D12Widget"
        QT_MOC_LITERAL(18, 13),  // "LoadResources"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 17),  // "deviceInitialized"
        QT_MOC_LITERAL(51, 7),  // "success"
        QT_MOC_LITERAL(59, 12),  // "eventHandled"
        QT_MOC_LITERAL(72, 13),  // "widgetResized"
        QT_MOC_LITERAL(86, 6),  // "ticked"
        QT_MOC_LITERAL(93, 8),  // "rendered"
        QT_MOC_LITERAL(102, 26),  // "ID3D12GraphicsCommandList*"
        QT_MOC_LITERAL(129, 2),  // "cl"
        QT_MOC_LITERAL(132, 10),  // "keyPressed"
        QT_MOC_LITERAL(143, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(154, 10),  // "mouseMoved"
        QT_MOC_LITERAL(165, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(178, 12),  // "mouseClicked"
        QT_MOC_LITERAL(191, 13),  // "mouseReleased"
        QT_MOC_LITERAL(205, 7),  // "onFrame"
        QT_MOC_LITERAL(213, 7)   // "onReset"
    },
    "QDirect3D12Widget",
    "LoadResources",
    "",
    "deviceInitialized",
    "success",
    "eventHandled",
    "widgetResized",
    "ticked",
    "rendered",
    "ID3D12GraphicsCommandList*",
    "cl",
    "keyPressed",
    "QKeyEvent*",
    "mouseMoved",
    "QMouseEvent*",
    "mouseClicked",
    "mouseReleased",
    "onFrame",
    "onReset"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QDirect3D12Widget[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    1,   87,    2, 0x06,    2 /* Public */,
       5,    0,   90,    2, 0x06,    4 /* Public */,
       6,    0,   91,    2, 0x06,    5 /* Public */,
       7,    0,   92,    2, 0x06,    6 /* Public */,
       8,    1,   93,    2, 0x06,    7 /* Public */,
      11,    1,   96,    2, 0x06,    9 /* Public */,
      13,    1,   99,    2, 0x06,   11 /* Public */,
      15,    1,  102,    2, 0x06,   13 /* Public */,
      16,    1,  105,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    0,  108,    2, 0x08,   17 /* Private */,
      18,    0,  109,    2, 0x08,   18 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 14,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QDirect3D12Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<ads::CDockWidget::staticMetaObject>(),
    qt_meta_stringdata_QDirect3D12Widget.offsetsAndSizes,
    qt_meta_data_QDirect3D12Widget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QDirect3D12Widget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QDirect3D12Widget, std::true_type>,
        // method 'LoadResources'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deviceInitialized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'eventHandled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'widgetResized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ticked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rendered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ID3D12GraphicsCommandList *, std::false_type>,
        // method 'keyPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'mouseMoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseReleased'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'onFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QDirect3D12Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QDirect3D12Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->LoadResources(); break;
        case 1: _t->deviceInitialized((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->eventHandled(); break;
        case 3: _t->widgetResized(); break;
        case 4: _t->ticked(); break;
        case 5: _t->rendered((*reinterpret_cast< std::add_pointer_t<ID3D12GraphicsCommandList*>>(_a[1]))); break;
        case 6: _t->keyPressed((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 7: _t->mouseMoved((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 8: _t->mouseClicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 9: _t->mouseReleased((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 10: _t->onFrame(); break;
        case 11: _t->onReset(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QDirect3D12Widget::*)();
            if (_t _q_method = &QDirect3D12Widget::LoadResources; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)(bool );
            if (_t _q_method = &QDirect3D12Widget::deviceInitialized; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)();
            if (_t _q_method = &QDirect3D12Widget::eventHandled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)();
            if (_t _q_method = &QDirect3D12Widget::widgetResized; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)();
            if (_t _q_method = &QDirect3D12Widget::ticked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)(ID3D12GraphicsCommandList * );
            if (_t _q_method = &QDirect3D12Widget::rendered; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)(QKeyEvent * );
            if (_t _q_method = &QDirect3D12Widget::keyPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)(QMouseEvent * );
            if (_t _q_method = &QDirect3D12Widget::mouseMoved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)(QMouseEvent * );
            if (_t _q_method = &QDirect3D12Widget::mouseClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (QDirect3D12Widget::*)(QMouseEvent * );
            if (_t _q_method = &QDirect3D12Widget::mouseReleased; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *QDirect3D12Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDirect3D12Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDirect3D12Widget.stringdata0))
        return static_cast<void*>(this);
    return ads::CDockWidget::qt_metacast(_clname);
}

int QDirect3D12Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ads::CDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void QDirect3D12Widget::LoadResources()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QDirect3D12Widget::deviceInitialized(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QDirect3D12Widget::eventHandled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QDirect3D12Widget::widgetResized()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QDirect3D12Widget::ticked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QDirect3D12Widget::rendered(ID3D12GraphicsCommandList * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QDirect3D12Widget::keyPressed(QKeyEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QDirect3D12Widget::mouseMoved(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QDirect3D12Widget::mouseClicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QDirect3D12Widget::mouseReleased(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
