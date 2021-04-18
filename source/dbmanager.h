#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QJsonObject>

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();
    virtual void save(const QJsonObject& object);
};

#endif // DBMANAGER_H
