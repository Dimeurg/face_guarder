#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "dbobject.h"
#include <vector>

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();
    virtual void save(const DBObject& object);
};

#endif // DBMANAGER_H
