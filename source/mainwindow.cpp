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

using namespace dlib;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    cv::VideoCapture cap(0);

    image_window win;
    frontal_face_detector detector = get_frontal_face_detector();

    const QString projectPath = PRJ_PATH;
    const QString modelName = "shape_predictor_68_face_landmarks.dat";

    shape_predictor pose_model;
    const QString path_model = projectPath + "/tools/model/" + modelName;

    deserialize(path_model.toStdString().c_str()) >> pose_model;

    while(!win.is_closed()){
        cv::Mat temp_img;

        if(!cap.read(temp_img)){
            break;
        }

        cv_image<bgr_pixel> img(temp_img);

        std::vector<rectangle> faces = detector(img);
        std::vector<full_object_detection> shapes;
        for(unsigned long i = 0; i < faces.size(); i++){
            shapes.push_back(pose_model(img, faces[i]));
        }

        cv_image<bgr_pixel> img_res(temp_img);
        if(!shapes.empty()){
            std::vector<cv::Point2l> points;
            for(int i = 0; i < 64; ++i){
                auto &part = shapes[0].part(i);
                points.emplace_back(part.x(), part.y());
            }
            for(cv::Point2l& point: points){
                cv::circle(temp_img, point, 2, cv::Scalar(0,0,255), -1);
            }
        }
        win.clear_overlay();
        win.set_image(img_res);
    }
}

MainWindow::~MainWindow()
{
}

