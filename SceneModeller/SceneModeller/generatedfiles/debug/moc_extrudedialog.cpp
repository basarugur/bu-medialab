/****************************************************************************
** Meta object code from reading C++ file 'extrudedialog.h'
**
** Created: Sun May 24 22:51:51 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../editing/extrudedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extrudedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExtrudeDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   14,   14,   14, 0x08,
      54,   14,   14,   14, 0x08,
      80,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ExtrudeDialog[] = {
    "ExtrudeDialog\0\0sceneChanged()\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_horizontalSlider_valueChanged(int)\0"
};

const QMetaObject ExtrudeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ExtrudeDialog,
      qt_meta_data_ExtrudeDialog, 0 }
};

const QMetaObject *ExtrudeDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ExtrudeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExtrudeDialog))
        return static_cast<void*>(const_cast< ExtrudeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ExtrudeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sceneChanged(); break;
        case 1: on_pushButton_clicked(); break;
        case 2: on_pushButton_2_clicked(); break;
        case 3: on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ExtrudeDialog::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
