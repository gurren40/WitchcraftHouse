/****************************************************************************
** Meta object code from reading C++ file 'websocketconnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../services/websocketconnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'websocketconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebsocketConnection_t {
    QByteArrayData data[15];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebsocketConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebsocketConnection_t qt_meta_stringdata_WebsocketConnection = {
    {
QT_MOC_LITERAL(0, 0, 19), // "WebsocketConnection"
QT_MOC_LITERAL(1, 20, 12), // "jsonReceived"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "json"
QT_MOC_LITERAL(4, 39, 4), // "pong"
QT_MOC_LITERAL(5, 44, 11), // "elapsedTime"
QT_MOC_LITERAL(6, 56, 7), // "payload"
QT_MOC_LITERAL(7, 64, 8), // "sendJson"
QT_MOC_LITERAL(8, 73, 11), // "onConnected"
QT_MOC_LITERAL(9, 85, 14), // "onDisconnected"
QT_MOC_LITERAL(10, 100, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(11, 122, 7), // "message"
QT_MOC_LITERAL(12, 130, 11), // "connectLoop"
QT_MOC_LITERAL(13, 142, 4), // "ping"
QT_MOC_LITERAL(14, 147, 6) // "onPong"

    },
    "WebsocketConnection\0jsonReceived\0\0"
    "json\0pong\0elapsedTime\0payload\0sendJson\0"
    "onConnected\0onDisconnected\0"
    "onTextMessageReceived\0message\0connectLoop\0"
    "ping\0onPong"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebsocketConnection[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   67,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,
      13,    0,   76,    2, 0x0a /* Public */,
      14,    2,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QByteArray,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QByteArray,    5,    6,

       0        // eod
};

void WebsocketConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebsocketConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->jsonReceived((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->pong((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->sendJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 3: _t->onConnected(); break;
        case 4: _t->onDisconnected(); break;
        case 5: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->connectLoop(); break;
        case 7: _t->ping(); break;
        case 8: _t->onPong((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebsocketConnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebsocketConnection::jsonReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebsocketConnection::*)(quint64 , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebsocketConnection::pong)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebsocketConnection::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WebsocketConnection.data,
    qt_meta_data_WebsocketConnection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WebsocketConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebsocketConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebsocketConnection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebsocketConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void WebsocketConnection::jsonReceived(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebsocketConnection::pong(quint64 _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
