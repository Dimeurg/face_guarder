#ifndef FACEPOINTS_H
#define FACEPOINTS_H

#include <vector>
#include "dbobject.h"

#include <opencv2/opencv.hpp>
#include <vector>

class FacePoints : public DBObject
{
public:
    FacePoints();
    virtual ~FacePoints();
    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject& object) override;
    virtual bool isValid() const override;

    void addPoint(cv::Point2l point);
    std::vector<cv::Point2l>::iterator begin();
    std::vector<cv::Point2l>::iterator end();

private:
    std::vector<cv::Point2l> points;
};

#endif // FACEPOINTS_H
