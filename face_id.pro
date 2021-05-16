QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/addercustomer.cpp \
    source/cameramanager.cpp \
    source/dbmanager.cpp \
    source/dbobject.cpp \
    source/face.cpp \
    source/facepoints.cpp \
    source/jsondb.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/recognizer.cpp

HEADERS += \
    source/addercustomer.h \
    source/cameramanager.h \
    source/dbmanager.h \
    source/dbobject.h \
    source/face.h \
    source/facepoints.h \
    source/jsondb.h \
    source/mainwindow.h \
    source/recognizer.h

DEFINES += PRJ_PATH='\\"$${PWD}\\"'

#opencv
INCLUDEPATH += G:/Dimeurg/programming/libs/OpenCV/build/install/include
INCLUDEPATH += G:/Dimeurg/programming/libs/OpenCV/build/install/x64/vc15/bin

#dlib
INCLUDEPATH += G:/Dimeurg/programming/libs/dlib/install/include
LIBS += -L"G:/Dimeurg/programming/libs/dlib/install/lib"

CONFIG( debug, debug|release ) {
    # debug
    LIBS += G:/Dimeurg/programming/libs/OpenCV/build/install/x64/vc15/lib/opencv_world451d.lib
    LIBS += -ldlib19.22.0_debug_64bit_msvc1916
} else {
    # release
    LIBS += G:/Dimeurg/programming/libs/OpenCV/build/install/x64/vc15/lib/opencv_world451.lib
    LIBS += -ldlib19.22.0_release_64bit_msvc1916
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



