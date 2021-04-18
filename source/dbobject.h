#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <QJsonObject>

class DBObject
{
public:
    DBObject();
    virtual ~DBObject();
    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject& object);
    virtual bool isValid() const;
};

#endif // DBOBJECT_H
