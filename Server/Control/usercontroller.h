#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>

class UserController : public QObject
{
    Q_OBJECT
public:
    explicit UserController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // USERCONTROLLER_H