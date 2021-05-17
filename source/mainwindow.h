#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "cameramanager.h"
#include "recognizer.h"
#include "addercustomer.h"

#include <QLabel>

#include <dlib/image_processing/frontal_face_detector.h>
#include "jsondb.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void addFrame(std::shared_ptr<std::vector<FacePoints>> pointSet);
    void addCustomer(QString name);

public slots:
    void onStartButton();
    void onStopButton();
    void onFrameReaded(cv::Mat frame);
    void onFrameRecognized(cv::Mat frame, std::shared_ptr<ProcessedFaces> processedFaces);
    void onAddNewCustomer();
    void onAddNewFrame();
private:
    void drawFrame(const cv::Mat frame);
    void drawCircles(cv::Mat frame, std::shared_ptr<std::vector<FacePoints>> facePoints);
    void stop();
    std::shared_ptr<std::vector<FacePoints>> getFacePoints(std::shared_ptr<ProcessedFaces> processedFaces);

    QGridLayout *layout;
    CameraManager camera;
    Recognizer recognizer;
    QLabel lbCameraFrame;
    cv::Mat currentFrame;
    FacePoints currentFace;
    std::shared_ptr<JsonDB> db;
    AdderCustomer adderCustomer;
    std::shared_ptr<std::vector<FacePoints>> currentPointsSet;
    QLineEdit lCustomerName;
    bool recognizerOn;
    bool cameraIsWorking;
};
#endif // MAINWINDOW_H
