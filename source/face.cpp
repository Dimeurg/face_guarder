#include "face.h"

#include <QJsonArray>

Face::Face()
{

}

Face::Face(const QString &name, const std::vector<FacePoints> &frames)
    : name(name), frames(frames)
{

}

Face::~Face()
{

}

QJsonObject Face::toJson() const
{
    QJsonObject result;
    if(isValid()){
        result["name"] = name;
        QJsonArray jFrames;
        for(auto& frame : frames){
            jFrames.append(frame.toJson());
        }
        result["points sets"] = jFrames;
    }
    return result;
}

void Face::fromJson(const QJsonObject &object)
{
    frames.clear();
    QJsonValue jValue = object.value("name");
    if(jValue.isString()){
        name = jValue.toString();
    }
    jValue = object.value("points sets");
    if(jValue.isArray()){
        QJsonArray points = jValue.toArray();
        QJsonArray::Iterator it;
        for(it = points.begin(); it != points.end(); ++it){
            FacePoints fPoints;
            fPoints.fromJson(it->toObject());
            if(fPoints.isValid()){
                frames.emplace_back(std::move(fPoints));
            }
        }
    }
}

bool Face::isValid() const
{
    if(name.isEmpty() || frames.empty()){
        return false;
    }
    for(auto& frame : frames){
        if(!frame.isValid()){
            return false;
        }
    }
    return true;
}

std::pair<QString, double> Face::compare(FacePoints &facePoints)
{
    bool valid = false;
    double difference = 0;
    for (auto & frame: frames){
        auto res = frame.compare(facePoints);
        if(res.first){
            if(!difference || difference > res.second){
                difference = res.second;
                valid = true;
            }
        }
    }
    QString resultName = valid ? name : QString();
    return std::pair<QString, double>(resultName, difference);
}














