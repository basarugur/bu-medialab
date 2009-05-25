/****************************************************************************
** Meta object code from reading C++ file 'smmenuhandler.h'
**
** Created: Sun May 24 22:51:49 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../editing/smmenuhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smmenuhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SMMenuHandler[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   14,   14,   14, 0x08,
      56,   14,   14,   14, 0x08,
      80,   14,   14,   14, 0x08,
      95,   14,   14,   14, 0x08,
     115,   14,   14,   14, 0x08,
     128,   14,   14,   14, 0x08,
     142,   14,   14,   14, 0x08,
     162,   14,   14,   14, 0x08,
     186,   14,   14,   14, 0x08,
     208,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SMMenuHandler[] = {
    "SMMenuHandler\0\0sceneChanged()\0"
    "updateWindowActions(bool)\0"
    "changeEditingMode(bool)\0addNewObject()\0"
    "changeEditingType()\0addNewItem()\0"
    "renderScene()\0fileActionClicked()\0"
    "editFaceActionEntered()\0cameraActionChanged()\0"
    "showHideToolbars(bool)\0"
};

const QMetaObject SMMenuHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SMMenuHandler,
      qt_meta_data_SMMenuHandler, 0 }
};

const QMetaObject *SMMenuHandler::metaObject() const
{
    return &staticMetaObject;
}

void *SMMenuHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SMMenuHandler))
        return static_cast<void*>(const_cast< SMMenuHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int SMMenuHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sceneChanged(); break;
        case 1: updateWindowActions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: changeEditingMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: addNewObject(); break;
        case 4: changeEditingType(); break;
        case 5: addNewItem(); break;
        case 6: renderScene(); break;
        case 7: fileActionClicked(); break;
        case 8: editFaceActionEntered(); break;
        case 9: cameraActionChanged(); break;
        case 10: showHideToolbars((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SMMenuHandler::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
