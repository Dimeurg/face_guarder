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
        result["points set"] = outputArray;
    }
    return result;
}

void FacePoints::fromJson(const QJsonObject &object)
{
    points.clear();
    QJsonValue jValue = object.value("points set");
    if(jValue.isArray()){
        QJsonArray points = jValue.toArray();
        QJsonArray::Iterator it;
        for(it = points.begin(); it != points.end(); ++it){
            auto point = it->toObject();
            int x = point.value("x").toInt();
            int y = point.value("y").toInt();
            addPoint(cv::Point2l(x, y));
        }
    }
}

bool FacePoints::isValid() const
{
    return points.size() == 64;
}

std::pair<bool, double> FacePoints::compare(FacePoints &facePoints)
{
    double difference = 0;
    for(auto point1 = begin(), point2 = facePoints.begin(); point1 != end() && point2 != facePoints.end(); ++point1, ++point2){
        difference += cv::norm(*point1 - *point2);
    }
    return std::pair<bool, double>(!points.empty(), difference);
}

void FacePoints::addPoint(cv::Point2l point)
{
    points.emplace_back(point);
}

std::vector<cv::Point2l>::iterator FacePoints::begin()
{
    return points.begin();
}

std::vector<cv::Point2l>::iterator FacePoints::end()
{
    return points.end();
}
