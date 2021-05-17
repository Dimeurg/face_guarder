#include "face.h"

#include <QJsonArray>

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
