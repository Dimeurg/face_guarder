#ifndef JSONDB_H
#define JSONDB_H

#include "dbmanager.h"
#include <QFile>
#include <QJsonObject>
#include "face.h"

class QJsonDocument;

class JsonDB : public DBManager
{
public:
    JsonDB();
    JsonDB(const QString& fileName);
    ~JsonDB();
    void setFileName(const QString& fileName);
    virtual void save(const DBObject& object) override;
    std::vector<Face> get();

private:
    void readJsonFile();
    void writeJsonFile();

    QString fileName;
    QFile jFile;
    QJsonObject jObj;
};

#endif // JSONDB_H
