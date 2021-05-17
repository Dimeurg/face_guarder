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
    QJsonValue jValue = jObj.value("faces");
    if(jValue.isUndefined()){
        jValue = QJsonArray();
        jObj["faces"] = jValue;
    }
    if(jValue.isArray()){
        QJsonArray faces = jValue.toArray();
        QJsonObject newCustomer = object.toJson();
        QString name = newCustomer.value("name").toString();
        if(!name.isEmpty()){
            QJsonArray::Iterator it;
            for(it = faces.begin(); it != faces.end(); ++it){
                QJsonObject currentCustomerInfo = it->toObject();
                QString currentName = currentCustomerInfo.value("name").toString();
                if(name == currentName){
                    break;
                }
            }
            if(it != faces.end()){
                (*it) = newCustomer;
            } else{
                faces.append(object.toJson());
            }
            jObj["faces"] = faces;
            writeJsonFile();
        } else{
            qDebug() << "invalid customer name";
        }
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
