//#ifndef CONNECTION_H
//#define CONNECTION_H

//#include <QObject>
//#include <QWebSocket>
//#include <QJsonDocument>
//#include <QJsonArray>
//#include <QJsonDocument>
//#include <QNetworkAccessManager>
//#include <QTimer>
//#include <QSettings>

//class Connection : public QObject
//{
//    Q_OBJECT
//public:
//    explicit Connection(QObject *parent = nullptr);
//    explicit Connection(QString server, QObject *parent = nullptr);

//signals:
//    void closed();
//    void messageReceived(QJsonObject json);

//public slots:
//    //koneksi ke /
//    void connectInit();
//    void connectMain();
//    void onConnected();
//    void onTextMessageReceived(QString message);
//    void sendMessage(QJsonObject json);
//    void startConnection();
//    void stopConnection();
//    void connectionLoop();

//private:
//    QWebSocket* m_websocket;
//    QString m_server;
//    QString jwt;
//    QTimer *m_timer;
//    QSettings *m_setting;
//};

//#endif // CONNECTION_H
