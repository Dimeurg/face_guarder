#include "facepoints.h"

#include <QJsonArray>

FacePoints::FacePoints()
{

}

FacePoints::~FacePoints()
{

}

QJsonObject FacePoints::toJson() const
{
    QJsonObject result;
    if(isValid()){
        QJsonArray outputArray;
        for(auto &point : points){
            QJsonObject JsonPoint;
            JsonPoint["x"] = point.x;
            JsonPoint["y"] = point.y;
            outputArray.append(JsonPoint);
        }
        result["points"] = outputArray;
    }
    return result;
}

void FacePoints::fromJson(const QJsonObject &object)
{

}

bool FacePoints::isValid() const
{
    return points.size() == 64;
}

void FacePoints::addPoint(cv::Point2l point)
{
    points.emplace_back(point);
}