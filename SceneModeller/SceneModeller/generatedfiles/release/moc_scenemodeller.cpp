/****************************************************************************
** Meta object code from reading C++ file 'scenemodeller.h'
**
** Created: Fri May 22 11:50:16 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scenemodeller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenemodeller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneModeller[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      43,   41,   14,   14, 0x08,
      77,   14,   14,   14, 0x08,
      91,   14,   14,   14, 0x08,
     118,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SceneModeller[] = {
    "SceneModeller\0\0changeCurrent(CanvasType)\0"
    ",\0changeFullScreen(CanvasType,bool)\0"
    "updateScene()\0centralWidgetSizeChanged()\0"
    "repaintCanvases()\0"
};

const QMetaObject SceneModeller::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SceneModeller,
      qt_meta_data_SceneModeller, 0 }
};

const QMetaObject *SceneModeller::metaObject() const
{
    return &staticMetaObject;
}

void *SceneModeller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneModeller))
        return static_cast<void*>(const_cast< SceneModeller*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SceneModeller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeCurrent((*reinterpret_cast< CanvasType(*)>(_a[1]))); break;
        case 1: changeFullScreen((*reinterpret_cast< CanvasType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: updateScene(); break;
        case 3: centralWidgetSizeChanged(); break;
        case 4: repaintCanvases(); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
