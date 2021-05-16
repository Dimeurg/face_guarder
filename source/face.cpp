#include "face.h"

#include <QJsonArray>

Face::Face()
{

}

Face::~Face()
{

}

QJsonObject Face::toJson() const
{
    QJsonObject result;
    if(isValid()){
        QJsonArray jFrames;
        for(auto& frame : frames){
            jFrames.append(frame.toJson());
        }
        result[name] = jFrames;
    }
    return result;
}

void Face::fromJson(const QJsonObject &object)
{

}

bool Face::isValid() const
{
    if(frames.empty()){
        return false;
    }
    for(auto& frame : frames){
        if(!frame.isValid()){
            return false;
        }
    }
    return true;
}
