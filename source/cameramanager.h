#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QThread>

class CameraManager : public QObject
{
    Q_OBJECT

public:
    CameraManager();

    void start();
    void stop();

public slots:
    void process();

signals:
    void frameReaded(cv::Mat frame);
    void finished();

private:
QThread thread;
bool isWorking;
cv::VideoCapture cap;
};

#endif // CAMERAMANAGER_H
