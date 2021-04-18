#include "jsondb.h"

#include <QFile>
#include <QJsonDocument>

JsonDB::JsonDB(const QString& fileName)
    :fileName(fileName)
{

}

JsonDB::~JsonDB()
{

}

void JsonDB::save(const QJsonObject& object)
{
    QFile jsonFile(fileName);
    if (jsonFile.open(QIODevice::WriteOnly))
    {
        QJsonDocument doc(object);
        jsonFile.write(doc.toJson(QJsonDocument::Indented));
        jsonFile.close();
    }
}
