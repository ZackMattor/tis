/****************************************************************************
** Meta object code from reading C++ file 'SessionManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "net/SessionManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SessionManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SessionManager_t {
    QByteArrayData data[27];
    char stringdata[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SessionManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SessionManager_t qt_meta_stringdata_SessionManager = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 14),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 3),
QT_MOC_LITERAL(4, 35, 15),
QT_MOC_LITERAL(5, 51, 6),
QT_MOC_LITERAL(6, 58, 6),
QT_MOC_LITERAL(7, 65, 13),
QT_MOC_LITERAL(8, 79, 12),
QT_MOC_LITERAL(9, 92, 8),
QT_MOC_LITERAL(10, 101, 15),
QT_MOC_LITERAL(11, 117, 7),
QT_MOC_LITERAL(12, 125, 6),
QT_MOC_LITERAL(13, 132, 18),
QT_MOC_LITERAL(14, 151, 5),
QT_MOC_LITERAL(15, 157, 4),
QT_MOC_LITERAL(16, 162, 13),
QT_MOC_LITERAL(17, 176, 6),
QT_MOC_LITERAL(18, 183, 4),
QT_MOC_LITERAL(19, 188, 10),
QT_MOC_LITERAL(20, 199, 11),
QT_MOC_LITERAL(21, 211, 7),
QT_MOC_LITERAL(22, 219, 4),
QT_MOC_LITERAL(23, 224, 16),
QT_MOC_LITERAL(24, 241, 13),
QT_MOC_LITERAL(25, 255, 8),
QT_MOC_LITERAL(26, 264, 8)
    },
    "SessionManager\0writeToConsole\0\0str\0"
    "packetValidated\0Packet\0packet\0"
    "responseReady\0QHostAddress\0receiver\0"
    "playerConnected\0Player*\0player\0"
    "playerDisconnected\0start\0stop\0"
    "processPacket\0sender\0port\0runCommand\0"
    "CommandType\0command\0args\0sendUpdatePacket\0"
    "checkTimeouts\0kickUser\0printWho\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SessionManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x05,
       4,    1,   82,    2, 0x05,
       7,    3,   85,    2, 0x05,
      10,    1,   92,    2, 0x05,
      13,    1,   95,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      14,    0,   98,    2, 0x0a,
      15,    0,   99,    2, 0x0a,
      16,    3,  100,    2, 0x0a,
      19,    2,  107,    2, 0x0a,
      23,    1,  112,    2, 0x0a,
      24,    0,  115,    2, 0x08,
      25,    1,  116,    2, 0x08,
      26,    0,  119,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 8, QMetaType::UShort,    6,    9,    2,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 8, QMetaType::UShort,    6,   17,   18,
    QMetaType::Void, 0x80000000 | 20, QMetaType::QStringList,   21,   22,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   22,
    QMetaType::Void,

       0        // eod
};

void SessionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SessionManager *_t = static_cast<SessionManager *>(_o);
        switch (_id) {
        case 0: _t->writeToConsole((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->packetValidated((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 2: _t->responseReady((*reinterpret_cast< Packet(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 3: _t->playerConnected((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 4: _t->playerDisconnected((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 5: _t->start(); break;
        case 6: _t->stop(); break;
        case 7: _t->processPacket((*reinterpret_cast< Packet(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 8: _t->runCommand((*reinterpret_cast< CommandType(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 9: _t->sendUpdatePacket((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 10: _t->checkTimeouts(); break;
        case 11: _t->kickUser((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 12: _t->printWho(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Packet >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Packet >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Packet >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Packet >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SessionManager::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SessionManager::writeToConsole)) {
                *result = 0;
            }
        }
        {
            typedef void (SessionManager::*_t)(Packet );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SessionManager::packetValidated)) {
                *result = 1;
            }
        }
        {
            typedef void (SessionManager::*_t)(Packet , const QHostAddress & , quint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SessionManager::responseReady)) {
                *result = 2;
            }
        }
        {
            typedef void (SessionManager::*_t)(Player * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SessionManager::playerConnected)) {
                *result = 3;
            }
        }
        {
            typedef void (SessionManager::*_t)(Player * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SessionManager::playerDisconnected)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject SessionManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SessionManager.data,
      qt_meta_data_SessionManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *SessionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SessionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SessionManager.stringdata))
        return static_cast<void*>(const_cast< SessionManager*>(this));
    return QObject::qt_metacast(_clname);
}

int SessionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SessionManager::writeToConsole(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SessionManager::packetValidated(Packet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SessionManager::responseReady(Packet _t1, const QHostAddress & _t2, quint16 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SessionManager::playerConnected(Player * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SessionManager::playerDisconnected(Player * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
