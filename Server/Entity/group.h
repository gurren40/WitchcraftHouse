#ifndef GROUP_H
#define GROUP_H

#include <QObject>

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GROUP_H