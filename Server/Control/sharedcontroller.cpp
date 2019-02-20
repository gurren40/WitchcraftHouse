#include "sharedcontroller.h"

SharedController::SharedController(QObject *parent) : QObject(parent)
{

}

SharedController::SharedController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void SharedController::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}
