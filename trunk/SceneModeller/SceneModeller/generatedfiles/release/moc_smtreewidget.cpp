/****************************************************************************
** Meta object code from reading C++ file 'smtreewidget.h'
**
** Created: Fri May 22 08:57:37 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../windows/smtreewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smtreewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SMTreeWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SMTreeWidget[] = {
    "SMTreeWidget\0\0src,dest\0"
    "dragDrop(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

const QMetaObject SMTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_SMTreeWidget,
      qt_meta_data_SMTreeWidget, 0 }
};

const QMetaObject *SMTreeWidget::metaObject() const
{
    return &staticMetaObject;
}

void *SMTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SMTreeWidget))
        return static_cast<void*>(const_cast< SMTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int SMTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dragDrop((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SMTreeWidget::dragDrop(QTreeWidgetItem * _t1, QTreeWidgetItem * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
