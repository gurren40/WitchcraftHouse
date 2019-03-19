#include "rep_service_source.h"
#include <QTextStream>
class Service : public ServiceSource
{
public:
    explicit Service(QObject *parent = nullptr);

public slots:
    void ping(const QString &msg);
};
