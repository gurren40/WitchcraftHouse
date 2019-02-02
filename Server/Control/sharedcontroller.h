#ifndef SHAREDCONTROLLER_H
#define SHAREDCONTROLLER_H

#include <QObject>

class SharedController : public QObject
{
    Q_OBJECT
public:
    explicit SharedController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SHAREDCONTROLLER_H