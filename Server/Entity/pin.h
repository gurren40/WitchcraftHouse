#ifndef PIN_H
#define PIN_H

#include <QObject>

class Pin : public QObject
{
    Q_OBJECT
public:
    explicit Pin(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PIN_H