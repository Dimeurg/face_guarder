#include "dbobject.h"

DBObject::DBObject()
{

}

DBObject::~DBObject()
{

}

QJsonObject DBObject::toJson() const
{
    return QJsonObject();
}

void DBObject::fromJson(const QJsonObject &object)
{
    Q_UNUSED(object)
}

bool DBObject::isValid() const
{
    return true;
}
