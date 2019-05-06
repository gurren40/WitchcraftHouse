#ifndef HUB_H
#define HUB_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSettings>

class Hub : public QObject
{
    Q_OBJECT
public:
    explicit Hub(QObject *parent = nullptr);

signals:
    void sendJsonToMain(QJsonObject json);
    void broadcastJson(QJsonObject json);

public:
    bool validateUUID(QString strUuid);

public slots:
    void jsonReceivedFromMain(QJsonObject json);
    void jsonReceivedFromClient(QJsonObject json);

private:
    int m_totalUuid;
    QList<QString> m_uuids;
};

#endif // HUB_H
