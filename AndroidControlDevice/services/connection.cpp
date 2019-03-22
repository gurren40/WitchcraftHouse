//#include "connection.h"
//#include <QDebug>

//Connection::Connection(QObject *parent) : QObject(parent)
//{

//}

//Connection::Connection(QString server, QObject *parent) : QObject(parent)
//{
//    m_websocket = new QWebSocket;
//    m_server = server;
//    m_timer = new QTimer(this);
//    connect(m_timer,&QTimer::timeout,this,&Connection::connectionLoop);
//    connect(m_websocket,&QWebSocket::connected,this,&Connection::onConnected);
//    connect(m_websocket,&QWebSocket::disconnected,this,&Connection::closed);
//}

//void Connection::startConnection()
//{
//    m_timer->start();
//}

//void Connection::stopConnection()
//{
//    m_timer->stop();
//}
