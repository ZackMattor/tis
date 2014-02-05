/****************************************************************************
** Meta object code from reading C++ file 'UdpServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "net/UdpServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UdpServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UdpServer_t {
    QByteArrayData data[23];
    char stringdata[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UdpServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UdpServer_t qt_meta_stringdata_UdpServer = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 14),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 6),
QT_MOC_LITERAL(4, 33, 6),
QT_MOC_LITERAL(5, 40, 12),
QT_MOC_LITERAL(6, 53, 6),
QT_MOC_LITERAL(7, 60, 4),
QT_MOC_LITERAL(8, 65, 14),
QT_MOC_LITERAL(9, 80, 3),
QT_MOC_LITERAL(10, 84, 10),
QT_MOC_LITERAL(11, 95, 11),
QT_MOC_LITERAL(12, 107, 7),
QT_MOC_LITERAL(13, 115, 4),
QT_MOC_LITERAL(14, 120, 12),
QT_MOC_LITERAL(15, 133, 8),
QT_MOC_LITERAL(16, 142, 20),
QT_MOC_LITERAL(17, 163, 11),
QT_MOC_LITERAL(18, 175, 28),
QT_MOC_LITERAL(19, 204, 5),
QT_MOC_LITERAL(20, 210, 4),
QT_MOC_LITERAL(21, 215, 4),
QT_MOC_LITERAL(22, 220, 5)
    },
    "UdpServer\0packetReceived\0\0Packet\0"
    "packet\0QHostAddress\0sender\0port\0"
    "writeToConsole\0str\0runCommand\0CommandType\0"
    "command\0args\0sendResponse\0receiver\0"
    "readPendingDatagrams\0socketError\0"
    "QAbstractSocket::SocketError\0error\0"
    "bind\0stop\0start\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   64,    2, 0x05,
       8,    1,   71,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      10,    2,   74,    2, 0x0a,
      14,    3,   79,    2, 0x0a,
      16,    0,   86,    2, 0x08,
      17,    1,   87,    2, 0x08,
      20,    1,   90,    2, 0x08,
      20,    1,   93,    2, 0x08,
      21,    0,   96,    2, 0x08,
      22,    0,   97,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::UShort,    4,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11, QMetaType::QStringList,   12,   13,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::UShort,    4,   15,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void, QMetaType::UShort,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UdpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UdpServer *_t = static_cast<UdpServer *>(_o);
        switch (_id) {
        case 0: _t->packetReceived((*reinterpret_cast< Packet(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 1: _t->writeToConsole((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->runCommand((*reinterpret_cast< CommandType(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 3: _t->sendResponse((*reinterpret_cast< Packet(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 4: _t->readPendingDatagrams(); break;
        case 5: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->bind((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 7: _t->bind((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->stop(); break;
        case 9: _t->start(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Packet >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Packet >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UdpServer::*_t)(Packet , const QHostAddress & , quint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpServer::packetReceived)) {
                *result = 0;
            }
        }
        {
            typedef void (UdpServer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpServer::writeToConsole)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject UdpServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpServer.data,
      qt_meta_data_UdpServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *UdpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpServer.stringdata))
        return static_cast<void*>(const_cast< UdpServer*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void UdpServer::packetReceived(Packet _t1, const QHostAddress & _t2, quint16 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpServer::writeToConsole(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
