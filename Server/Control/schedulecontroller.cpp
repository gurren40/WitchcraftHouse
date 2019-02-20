#include "schedulecontroller.h"

ScheduleController::ScheduleController(QObject *parent) : QObject(parent)
{

}

ScheduleController::ScheduleController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void ScheduleController::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}
