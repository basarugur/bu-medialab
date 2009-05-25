/****************************************************************************
** Meta object code from reading C++ file 'editcamera.h'
**
** Created: Sun May 24 22:51:52 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Camera/editcamera.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editcamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditCamera[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      25,   11,   11,   11, 0x0a,
      50,   11,   11,   11, 0x0a,
      73,   11,   11,   11, 0x0a,
      98,   11,   11,   11, 0x0a,
     119,   11,   11,   11, 0x08,
     145,   11,   11,   11, 0x08,
     171,   11,   11,   11, 0x08,
     190,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EditCamera[] = {
    "EditCamera\0\0showDialog()\0"
    "currentPositionChanged()\0"
    "currentTargetChanged()\0currentUpVectorChanged()\0"
    "currentNameChanged()\0on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0on_Close_clicked()\0"
    "on_Add_clicked()\0on_listWidget_currentRowChanged(int)\0"
};

const QMetaObject EditCamera::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditCamera,
      qt_meta_data_EditCamera, 0 }
};

const QMetaObject *EditCamera::metaObject() const
{
    return &staticMetaObject;
}

void *EditCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditCamera))
        return static_cast<void*>(const_cast< EditCamera*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showDialog(); break;
        case 1: currentPositionChanged(); break;
        case 2: currentTargetChanged(); break;
        case 3: currentUpVectorChanged(); break;
        case 4: currentNameChanged(); break;
        case 5: on_pushButton_2_clicked(); break;
        case 6: on_pushButton_3_clicked(); break;
        case 7: on_Close_clicked(); break;
        case 8: on_Add_clicked(); break;
        case 9: on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
