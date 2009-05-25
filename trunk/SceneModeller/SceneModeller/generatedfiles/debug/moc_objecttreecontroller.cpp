/****************************************************************************
** Meta object code from reading C++ file 'objecttreecontroller.h'
**
** Created: Sun May 24 22:51:51 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../windows/objecttreecontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objecttreecontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ObjectTreeController[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   37,   21,   21, 0x0a,
      74,   62,   21,   21, 0x0a,
     118,  109,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ObjectTreeController[] = {
    "ObjectTreeController\0\0sceneChanged()\0"
    "sh_\0showDockWidget(bool)\0item,column\0"
    "selectObject(QTreeWidgetItem*,int)\0"
    "src,dest\0itemsDragDroped(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

const QMetaObject ObjectTreeController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ObjectTreeController,
      qt_meta_data_ObjectTreeController, 0 }
};

const QMetaObject *ObjectTreeController::metaObject() const
{
    return &staticMetaObject;
}

void *ObjectTreeController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectTreeController))
        return static_cast<void*>(const_cast< ObjectTreeController*>(this));
    return QObject::qt_metacast(_clname);
}

int ObjectTreeController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sceneChanged(); break;
        case 1: showDockWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: selectObject((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: itemsDragDroped((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ObjectTreeController::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
