#include "mainwindow.h"

#include <QDir>

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/gui_widgets.h>

#include <iostream>

#include <QImage>
#include <QPixmap>
#include <QLabel>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

using namespace dlib;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),  db(std::make_shared<JsonDB>()), adderCustomer(db), recognizerOn(true), cameraIsWorking(false), faceIdentifier(db, 3000)
{

    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< std::shared_ptr<ProcessedFaces> >("std::shared_ptr<ProcessedFaces>");

    const QString projectPath = PRJ_PATH;
    const QString jFileName = "faces.json";
    const QString jFilePath = projectPath + "/tools/faces/" + jFileName;
    db->setFileName(jFilePath);

    resize(1400, 700);
    QWidget * centralWidget = new QWidget(this);
    QHBoxLayout * mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(50);
    setCentralWidget(centralWidget);

    //// layout control buttons
    QVBoxLayout * lControlButtons = new QVBoxLayout();

    QPushButton * bStart = new QPushButton("start");
    QPushButton * bStop = new QPushButton("stop");
    connect(bStart, &QPushButton::clicked, this, &MainWindow::onStartButton);
    connect(bStop, &QPushButton::clicked, this, &MainWindow::onStopButton);

    lControlButtons->addStretch();
    lControlButtons->addWidget(bStart);
    lControlButtons->addWidget(bStop);
    lControlButtons->addStretch();

    QWidget * wControlButtons = new QWidget();
    wControlButtons->setLayout(lControlButtons);

    QSizePolicy spControlButtons(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spControlButtons.setHorizontalStretch(1);
    wControlButtons->setSizePolicy(spControlButtons);
    ////

    //// layout frame
    lbCameraFrame.setAutoFillBackground(true);
    lbCameraFrame.setPalette(QPalette(Qt::black));

    QSizePolicy frameSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameSizePolicy.setHorizontalStretch(3);
    lbCameraFrame.setSizePolicy(frameSizePolicy);
    ////

    //// layout add new customer
    QVBoxLayout * lAddNewCustomer = new QVBoxLayout();

    QPushButton * bAddFrame = new QPushButton("add frame");
    QPushButton * bAddCustomer = new QPushButton("add customer");
    QPushButton * bRestoreFrames = new QPushButton("restore frames");
    QLabel * lbFrameCounts = new QLabel("frame counts: 0");
    lbFrameCounts->setAlignment(Qt::AlignCenter);

    connect(bAddFrame, &QPushButton::clicked, this, &MainWindow::onAddNewFrame);
    connect(bAddCustomer, &QPushButton::clicked, this, &MainWindow::onAddNewCustomer);
    connect(bRestoreFrames, &QPushButton::clicked, &adderCustomer, &AdderCustomer::onRestoreFrames);

    connect(this, &MainWindow::addFrame, &adderCustomer, &AdderCustomer::onAddFrame);
    connect(this, &MainWindow::addCustomer, &adderCustomer, &AdderCustomer::onAddCustomer);
    connect(&adderCustomer, &AdderCustomer::changedFramesCount, lbFrameCounts, &QLabel::setText);
    connect(&faceIdentifier, &FaceIdentifier::identified, this, &MainWindow::onFoundCustomer);

    lAddNewCustomer->addStretch();
    lAddNewCustomer->addWidget(&lCustomerName);
    lAddNewCustomer->addWidget(lbFrameCounts);
    lAddNewCustomer->addWidget(bAddFrame);
    lAddNewCustomer->addWidget(bAddCustomer);
    lAddNewCustomer->addWidget(bRestoreFrames);
    lAddNewCustomer->addWidget(&lFoundName);
    lAddNewCustomer->addStretch();

    QWidget * wAddNewCustomer = new QWidget();
    wAddNewCustomer->setLayout(lAddNewCustomer);
    QSizePolicy spAddNewCustomer(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spAddNewCustomer.setHorizontalStretch(1);
    wAddNewCustomer->setSizePolicy(spAddNewCustomer);
    ////

    connect(&camera, &CameraManager::frameReaded, this, &MainWindow::onFrameReaded);
    connect(&recognizer, &Recognizer::recognized, this, &MainWindow::onFrameRecognized);;

    mainLayout->addWidget(wControlButtons);
    mainLayout->addWidget(&lbCameraFrame);
    mainLayout->addWidget(wAddNewCustomer);
}

void MainWindow::onStartButton()
{
    camera.start();
    recognizer.start();
    cameraIsWorking = true;
}

void MainWindow::onStopButton()
{
    stop();
}

void MainWindow::onFrameReaded(cv::Mat frame)
{
    if(recognizerOn){
        recognizer.newFrame(frame);
    }
    else{
        drawFrame(frame);
    }
}

void MainWindow::onFrameRecognized(cv::Mat frame, std::shared_ptr<ProcessedFaces> processedFaces)
{
    currentPointsSet = getFacePoints(processedFaces);
    if(!currentPointsSet->empty()){
        currentFace = (*currentPointsSet)[0];
        faceIdentifier.identify(currentFace);
    }
    else{
        currentFace = FacePoints();
        onFoundCustomer(QString());
    }

    drawCircles(frame, currentPointsSet);
    drawFrame(frame);
}

void MainWindow::onAddNewCustomer()
{
    QString name = lCustomerName.text();
    if(!name.isEmpty()){
        emit addCustomer(name);
    }
}

void MainWindow::onAddNewFrame()
{
    if(currentPointsSet && !currentPointsSet->empty()){
        emit addFrame(currentPointsSet);
    }
}

void MainWindow::onFoundCustomer(QString name)
{
    if(!name.isEmpty()){
        lFoundName.setText(name);
    }
    else{
        lFoundName.setText("undefined");
    }
    qDebug() << name;
}

void MainWindow::drawFrame(const cv::Mat frame)
{
    if(cameraIsWorking){
        QImage originalImg = QImage((uchar*)(frame.data), frame.cols, frame.rows,QImage::Format_RGB888);
        QImage resultImg = originalImg.scaled(lbCameraFrame.frameSize(), Qt::KeepAspectRatio);

        lbCameraFrame.setPixmap(QPixmap::fromImage(resultImg.rgbSwapped()));
    }
}

void MainWindow::drawCircles(cv::Mat frame, std::shared_ptr<std::vector<FacePoints>> facePoints)
{
    for(auto& face : *facePoints){
        if(face.isValid()){
            for(cv::Point2l& point : face){
                cv::circle(frame, point, 2, cv::Scalar(0,0,255), -1);
            }
        }
    }
}

std::shared_ptr<std::vector<FacePoints>> MainWindow::getFacePoints(std::shared_ptr<ProcessedFaces> processedFaces)
{
    std::shared_ptr<std::vector<FacePoints>> result = std::make_shared<std::vector<FacePoints>>();
    for(auto& face : *processedFaces){
        FacePoints facePoints;
        for(int i = 0; i < 64; ++i){
            auto &part = face.part(i);
            facePoints.addPoint(cv::Point2l(part.x(), part.y()));
        }
        if(facePoints.isValid()){
            result->push_back(facePoints);
        }
    }
    return result;
}

void MainWindow::stop(){
    camera.stop();
    recognizer.stop();
    lbCameraFrame.clear();
    cameraIsWorking = false;
}





















