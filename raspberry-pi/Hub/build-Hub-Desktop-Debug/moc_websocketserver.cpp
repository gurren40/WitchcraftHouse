/****************************************************************************
** Meta object code from reading C++ file 'websocketserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../services/websocketserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'websocketserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebsocketServer_t {
    QByteArrayData data[11];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebsocketServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebsocketServer_t qt_meta_stringdata_WebsocketServer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WebsocketServer"
QT_MOC_LITERAL(1, 16, 12), // "jsonReceived"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "json"
QT_MOC_LITERAL(4, 35, 6), // "closed"
QT_MOC_LITERAL(5, 42, 15), // "onNewConnection"
QT_MOC_LITERAL(6, 58, 18), // "processTextMessage"
QT_MOC_LITERAL(7, 77, 7), // "message"
QT_MOC_LITERAL(8, 85, 20), // "processBinaryMessage"
QT_MOC_LITERAL(9, 106, 18), // "socketDisconnected"
QT_MOC_LITERAL(10, 125, 8) // "sendJson"

    },
    "WebsocketServer\0jsonReceived\0\0json\0"
    "closed\0onNewConnection\0processTextMessage\0"
    "message\0processBinaryMessage\0"
    "socketDisconnected\0sendJson"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebsocketServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,
       9,    0,   60,    2, 0x0a /* Public */,
      10,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    3,

       0        // eod
};

void WebsocketServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebsocketServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->jsonReceived((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->closed(); break;
        case 2: _t->onNewConnection(); break;
        case 3: _t->processTextMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->processBinaryMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->socketDisconnected(); break;
        case 6: _t->sendJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebsocketServer::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebsocketServer::jsonReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebsocketServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebsocketServer::closed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebsocketServer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WebsocketServer.data,
    qt_meta_data_WebsocketServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WebsocketServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebsocketServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebsocketServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebsocketServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WebsocketServer::jsonReceived(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebsocketServer::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
