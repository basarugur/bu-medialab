/****************************************************************************
** Meta object code from reading C++ file 'camerapropertiescontroller.h'
**
** Created: Sun May 24 22:51:52 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../windows/camerapropertiescontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerapropertiescontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CameraController[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   33,   17,   17, 0x0a,
      58,   17,   17,   17, 0x0a,
      77,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CameraController[] = {
    "CameraController\0\0sceneChanged()\0sh_\0"
    "showDockWidget(bool)\0updateCameraInfo()\0"
    "lineEditsChanged()\0"
};

const QMetaObject CameraController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CameraController,
      qt_meta_data_CameraController, 0 }
};

const QMetaObject *CameraController::metaObject() const
{
    return &staticMetaObject;
}

void *CameraController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraController))
        return static_cast<void*>(const_cast< CameraController*>(this));
    return QObject::qt_metacast(_clname);
}

int CameraController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sceneChanged(); break;
        case 1: showDockWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: updateCameraInfo(); break;
        case 3: lineEditsChanged(); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CameraController::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
