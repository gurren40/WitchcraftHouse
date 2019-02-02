#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H

#include <QObject>

class ScheduleController : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SCHEDULECONTROLLER_H