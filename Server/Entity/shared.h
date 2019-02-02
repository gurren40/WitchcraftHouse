#ifndef SHARED_H
#define SHARED_H

#include <QObject>

class Shared : public QObject
{
    Q_OBJECT
public:
    explicit Shared(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SHARED_H