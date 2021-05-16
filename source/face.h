#ifndef FACE_H
#define FACE_H

#include "facepoints.h"

class Face : public DBObject
{
public:
    Face();
    virtual ~Face();
    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject& object) override;
    virtual bool isValid() const override;

private:
    std::vector<FacePoints> frames;
    QString name;
};

#endif // FACE_H
