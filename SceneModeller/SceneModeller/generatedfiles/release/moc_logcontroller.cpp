/****************************************************************************
** Meta object code from reading C++ file 'logcontroller.h'
**
** Created: Fri May 22 08:57:37 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../windows/logcontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogController[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LogController[] = {
    "LogController\0\0sh_\0showDockWidget(bool)\0"
};

const QMetaObject LogController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LogController,
      qt_meta_data_LogController, 0 }
};

const QMetaObject *LogController::metaObject() const
{
    return &staticMetaObject;
}

void *LogController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogController))
        return static_cast<void*>(const_cast< LogController*>(this));
    return QObject::qt_metacast(_clname);
}

int LogController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showDockWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
