#ifndef FACEIDENTIFIER_H
#define FACEIDENTIFIER_H

#include <QObject>

#include "facepoints.h"
#include "dbmanager.h"
#include "jsondb.h"

class FaceIdentifier : public QObject
{
    Q_OBJECT

public:
    FaceIdentifier(std::shared_ptr<JsonDB> db, double diff);

public slots:
    void identify(FacePoints pointSet);

signals:
    void identified(QString name);

private:
    std::shared_ptr<JsonDB> db;
    double diff;
};

#endif // FACEIDENTIFIER_H

