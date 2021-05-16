#include "cameramanager.h"
#include <QDebug>

CameraManager::CameraManager()
    : isWorking(false)
{
    cap.open(cv::CAP_ANY);
    connect(&thread, &QThread::started, this, &CameraManager::process);
    connect(this, &CameraManager::finished, &thread, &QThread::quit);
    moveToThread(&thread);
}

void CameraManager::start()
{
    if(!isWorking){
        isWorking = true;
        thread.start();
    }
}

void CameraManager::stop()
{
    if(isWorking){
        isWorking = false;
    }
}

void CameraManager::process()
{
    while(isWorking){
        cv::Mat temp_img;

        if(cap.read(temp_img)){
            emit frameReaded(temp_img);
        }
    }
    emit finished();
}
