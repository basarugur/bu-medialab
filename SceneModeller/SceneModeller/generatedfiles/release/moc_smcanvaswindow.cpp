/****************************************************************************
** Meta object code from reading C++ file 'smcanvaswindow.h'
**
** Created: Fri May 22 11:50:16 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../canvas/smcanvaswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smcanvaswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SMCanvasWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      42,   40,   15,   15, 0x05,
      74,   15,   15,   15, 0x05,
      90,   15,   15,   15, 0x05,
     105,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,   15,   15,   15, 0x08,
     138,   15,   15,   15, 0x08,
     155,   15,   15,   15, 0x08,
     176,  172,   15,   15, 0x08,
     197,   15,   15,   15, 0x08,
     216,   15,   15,   15, 0x08,
     230,   15,   15,   15, 0x08,
     244,   15,   15,   15, 0x08,
     268,   15,   15,   15, 0x08,
     287,   15,   15,   15, 0x08,
     306,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SMCanvasWindow[] = {
    "SMCanvasWindow\0\0makeCurrent(CanvasType)\0"
    ",\0makeFullScreen(CanvasType,bool)\0"
    "cameraUpdated()\0sceneChanged()\0"
    "canvasRepainted()\0showGrid(bool)\0"
    "show1xGrid(bool)\0show5xGrid(bool)\0fl_\0"
    "showFullScreen(bool)\0updateCameraList()\0"
    "resetCamera()\0shiftCamera()\0"
    "changeDrawingType(bool)\0changeCameraTool()\0"
    "showTreePath(bool)\0showItems(bool)\0"
};

const QMetaObject SMCanvasWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SMCanvasWindow,
      qt_meta_data_SMCanvasWindow, 0 }
};

const QMetaObject *SMCanvasWindow::metaObject() const
{
    return &staticMetaObject;
}

void *SMCanvasWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SMCanvasWindow))
        return static_cast<void*>(const_cast< SMCanvasWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int SMCanvasWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: makeCurrent((*reinterpret_cast< CanvasType(*)>(_a[1]))); break;
        case 1: makeFullScreen((*reinterpret_cast< CanvasType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: cameraUpdated(); break;
        case 3: sceneChanged(); break;
        case 4: canvasRepainted(); break;
        case 5: showGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: show1xGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: show5xGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: showFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: updateCameraList(); break;
        case 10: resetCamera(); break;
        case 11: shiftCamera(); break;
        case 12: changeDrawingType((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: changeCameraTool(); break;
        case 14: showTreePath((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: showItems((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SMCanvasWindow::makeCurrent(CanvasType _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SMCanvasWindow::makeFullScreen(CanvasType _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SMCanvasWindow::cameraUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SMCanvasWindow::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SMCanvasWindow::canvasRepainted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
