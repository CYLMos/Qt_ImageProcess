#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T22:27:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_Process
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Decoder.cpp \
    Encoder.cpp

HEADERS  += mainwindow.h \
    Decoder.h \
    Encoder.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:\build\include\opencv\
               D:\build\include\opencv2\
               D:\build\include

LIBS+=D:\build\lib\libopencv_calib3d310.dll.a\
D:\build\lib\libopencv_core310.dll.a\
D:\build\lib\libopencv_features2d310.dll.a\
D:\build\lib\libopencv_flann310.dll.a\
D:\build\lib\libopencv_highgui310.dll.a\
D:\build\lib\libopencv_imgproc310.dll.a\
D:\build\lib\libopencv_imgcodecs310.dll.a\
D:\build\lib\libopencv_ml310.dll.a\
D:\build\lib\libopencv_objdetect310.dll.a\
D:\build\lib\libopencv_video310.dll.a

DISTFILES += \
    haarcascade_frontalface_alt.xml
