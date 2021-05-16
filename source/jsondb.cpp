#include "jsondb.h"

#include "QJsonDocument"
#include "QJsonArray"

#include "QDebug"

JsonDB::JsonDB()
{

}

JsonDB::JsonDB(const QString& fileName)
    :fileName(fileName), jFile(fileName)
{
    readJsonFile();
}

JsonDB::~JsonDB()
{

}

void JsonDB::setFileName(const QString &fileName)
{
    this->fileName = fileName;
    jFile.setFileName(this->fileName);
    readJsonFile();
}

void JsonDB::save(const DBObject& object)
{
    QJsonValue jValue = jObj.value(QString("faces"));
    if(jValue.isUndefined()){
        jValue = QJsonArray();
        jObj["faces"] = jValue;
    }
    if(jValue.isArray()){
        QJsonArray faces = jValue.toArray();
        faces.append(object.toJson());
        jObj["faces"] = faces;
        writeJsonFile();
    }
    else{
        qDebug() << "json db values isn't array";
    }
}

void JsonDB::readJsonFile()
{
    if(jFile.open(QIODevice::ReadOnly)){
        QString text;
        text = jFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
        jObj = doc.object();
        jFile.close();
    }
}

void JsonDB::writeJsonFile()
{
    if (jFile.open(QIODevice::WriteOnly))
    {
        QJsonDocument doc(jObj);
        jFile.write(doc.toJson(QJsonDocument::Indented));
        jFile.close();
    }
}
