#ifndef JSONDB_H
#define JSONDB_H

#include "dbmanager.h"

class JsonDB : public DBManager
{
public:
    JsonDB(const QString& fileName);
    ~JsonDB();
    virtual void save(const QJsonObject& object);

private:
    QString fileName;
};

#endif // JSONDB_H
