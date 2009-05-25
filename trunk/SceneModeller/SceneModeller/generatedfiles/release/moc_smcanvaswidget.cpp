/****************************************************************************
** Meta object code from reading C++ file 'smcanvaswidget.h'
**
** Created: Sun May 24 22:06:56 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../canvas/smcanvaswidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smcanvaswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SMCanvasWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_SMCanvasWidget[] = {
    "SMCanvasWidget\0"
};

const QMetaObject SMCanvasWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_SMCanvasWidget,
      qt_meta_data_SMCanvasWidget, 0 }
};

const QMetaObject *SMCanvasWidget::metaObject() const
{
    return &staticMetaObject;
}

void *SMCanvasWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SMCanvasWidget))
        return static_cast<void*>(const_cast< SMCanvasWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int SMCanvasWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
