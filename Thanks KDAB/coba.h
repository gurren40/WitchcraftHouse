#ifndef COBA_H
#define COBA_H

#include <QObject>
#include <QAndroidJniObject>
#include <QDebug>

class Coba : public QObject
{
    Q_OBJECT
public:
    explicit Coba(QObject *parent = nullptr);

    QString path() const;
    void setPath(const QString &path = "com/kdab/training/ServiceQt");

signals:

public slots:

    void notification(QString msg = "bweeee");

private:
    QString m_path;
};

#endif // COBA_H
