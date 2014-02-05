/****************************************************************************
** Meta object code from reading C++ file 'Console.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "console/Console.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Console.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Console_t {
    QByteArrayData data[14];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Console_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Console_t qt_meta_stringdata_Console = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 14),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 11),
QT_MOC_LITERAL(4, 36, 4),
QT_MOC_LITERAL(5, 41, 4),
QT_MOC_LITERAL(6, 46, 5),
QT_MOC_LITERAL(7, 52, 4),
QT_MOC_LITERAL(8, 57, 9),
QT_MOC_LITERAL(9, 67, 4),
QT_MOC_LITERAL(10, 72, 9),
QT_MOC_LITERAL(11, 82, 6),
QT_MOC_LITERAL(12, 89, 12),
QT_MOC_LITERAL(13, 102, 7)
    },
    "Console\0commandEntered\0\0CommandType\0"
    "type\0args\0write\0data\0writeLine\0line\0"
    "readStdin\0socket\0parseCommand\0command\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Console[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    1,   44,    2, 0x0a,
       8,    1,   47,    2, 0x0a,
      10,    1,   50,    2, 0x08,
      12,    1,   53,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QStringList,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void Console::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Console *_t = static_cast<Console *>(_o);
        switch (_id) {
        case 0: _t->commandEntered((*reinterpret_cast< CommandType(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 1: _t->write((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->writeLine((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->readStdin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->parseCommand((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Console::*_t)(CommandType , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Console::commandEntered)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Console::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Console.data,
      qt_meta_data_Console,  qt_static_metacall, 0, 0}
};


const QMetaObject *Console::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Console::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Console.stringdata))
        return static_cast<void*>(const_cast< Console*>(this));
    return QObject::qt_metacast(_clname);
}

int Console::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Console::commandEntered(CommandType _t1, QStringList _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
