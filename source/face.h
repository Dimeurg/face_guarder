#ifndef FACE_H
#define FACE_H

#include "facepoints.h"

class Face : public DBObject
{
public:
    Face();
    Face(const QString & name, const std::vector<FacePoints>& frames);
    virtual ~Face();
    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject& object) override;
    virtual bool isValid() const override;
    std::pair<QString, double> compare(FacePoints& facePoints);

private:
    QString name;
    std::vector<FacePoints> frames;
};

#endif // FACE_H
