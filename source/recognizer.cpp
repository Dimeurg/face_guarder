#include "recognizer.h"

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/gui_widgets.h>

#include <QCoreApplication>

Recognizer::Recognizer()
    :isWorking(false), detector(dlib::get_frontal_face_detector())
{
    const QString projectPath = PRJ_PATH;
    const QString modelName = "shape_predictor_68_face_landmarks.dat";
    const QString path_model = projectPath + "/tools/model/" + modelName;

    dlib::deserialize(path_model.toStdString().c_str()) >> poseModel;

    connect(&thread, &QThread::started, this, &Recognizer::process);
    connect(this, &Recognizer::finished, &thread, &QThread::quit);
    //connect(this, &Recognizer::finished, this, &Recognizer::deleteLater);

    moveToThread(&thread);
}

void Recognizer::start()
{
    if(!isWorking){
        isWorking = true;
        thread.start();
    }
}

void Recognizer::stop()
{
    if(isWorking){
        isWorking = false;
    }
}

void Recognizer::wait()
{
    thread.wait();
}

void Recognizer::process()
{
    while(isWorking){
        mutex.lock();
        cv::Mat currentFrame = bufferedFrame.clone();
        mutex.unlock();

        if(currentFrame.empty()){
            continue;
        }

        dlib::cv_image<dlib::bgr_pixel> img(currentFrame);
        FoundFaces faces = detector(img);

        std::shared_ptr<ProcessedFaces> shapes = std::make_shared<ProcessedFaces>();
        for(unsigned long i = 0; i < faces.size(); i++){
            shapes->push_back(poseModel(img, faces[i]));
        }

        emit recognized(currentFrame, shapes);
    }

    emit finished();
    QCoreApplication::processEvents();
}

void Recognizer::newFrame(cv::Mat frame)
{
    mutex.lock();
    bufferedFrame = frame;
    mutex.unlock();
}
