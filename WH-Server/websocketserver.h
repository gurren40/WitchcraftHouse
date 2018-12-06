#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // WEBSOCKETSERVER_H