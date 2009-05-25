/****************************************************************************
** Meta object code from reading C++ file 'objectpropertiescontroller.h'
**
** Created: Sun May 24 22:06:56 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../windows/objectpropertiescontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectpropertiescontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ObjectPropertiesController[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   43,   27,   27, 0x0a,
      68,   27,   27,   27, 0x0a,
      87,   27,   27,   27, 0x0a,
     101,   27,   27,   27, 0x0a,
     117,   27,   27,   27, 0x0a,
     136,   27,   27,   27, 0x0a,
     158,   27,   27,   27, 0x0a,
     176,   27,   27,   27, 0x0a,
     195,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ObjectPropertiesController[] = {
    "ObjectPropertiesController\0\0sceneChanged()\0"
    "sh_\0showDockWidget(bool)\0lineEditsChanged()\0"
    "changeColor()\0changeTexture()\0"
    "cameraPosChanged()\0cameraTargetChanged()\0"
    "cameraUpChanged()\0textureOnOff(bool)\0"
    "changeTexturePlane(int)\0"
};

const QMetaObject ObjectPropertiesController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ObjectPropertiesController,
      qt_meta_data_ObjectPropertiesController, 0 }
};

const QMetaObject *ObjectPropertiesController::metaObject() const
{
    return &staticMetaObject;
}

void *ObjectPropertiesController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectPropertiesController))
        return static_cast<void*>(const_cast< ObjectPropertiesController*>(this));
    return QObject::qt_metacast(_clname);
}

int ObjectPropertiesController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sceneChanged(); break;
        case 1: showDockWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: lineEditsChanged(); break;
        case 3: changeColor(); break;
        case 4: changeTexture(); break;
        case 5: cameraPosChanged(); break;
        case 6: cameraTargetChanged(); break;
        case 7: cameraUpChanged(); break;
        case 8: textureOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: changeTexturePlane((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ObjectPropertiesController::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
