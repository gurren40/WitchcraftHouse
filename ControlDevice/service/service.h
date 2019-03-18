#include "rep_service_source.h"
#include <QTextStream>
class Service : public ServiceSource
{
public slots:
    void ping(const QString &msg);
};
