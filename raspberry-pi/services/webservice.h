#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <QObject>
#include <QSettings>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

struct Pin{
    QString uuid;
    QString server;
};

class WebService : public QObject
{
    Q_OBJECT
public:
    explicit WebService(QObject *parent = nullptr);

signals:
    void jsonReceived(QJsonObject json);

public slots:
    void sendJson(QJsonObject json);
    void loop();
    void requestFinished();

private:
    Pin getPinDataAt(int i);
    int m_totalUuid;
    QList<Pin> m_pins;
    QTimer *m_timer;
    QNetworkAccessManager *m_networkManager;
};

#endif // WEBSERVICE_H
