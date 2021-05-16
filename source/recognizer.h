#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

#include <QThread>
#include <QObject>
#include <QMutex>

using FoundFaces = std::vector<dlib::rectangle>;
using ProcessedFace = dlib::full_object_detection;
using ProcessedFaces = std::vector<ProcessedFace>;

class Recognizer : public QObject
{
    Q_OBJECT
public:
    Recognizer();

    void start();
    void stop();
    void wait();
    void newFrame(cv::Mat frame);

public slots:
    void process();

signals:
    void recognized(cv::Mat frame, std::shared_ptr<ProcessedFaces> shapes);
    void finished();

private:
    bool isWorking;
    dlib::shape_predictor poseModel;
    dlib::frontal_face_detector detector;
    cv::Mat bufferedFrame;
    QMutex mutex;
    QThread thread;
};

#endif // RECOGNIZER_H
