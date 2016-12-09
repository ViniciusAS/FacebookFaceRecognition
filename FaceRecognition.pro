TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    FaceRecognitionQueue.cpp \
    FaceRecognizer.cpp \
    AppWindow.cpp \
    ObjectDetector.cpp \
    VideoArea.cpp

DISTFILES += \
    installOpenCV_latest.sh \
    faces.csv \
    labels.csv \
    .gitignore

HEADERS += \
    FaceRecognitionQueue.h \
    FaceRecognizer.h \
    AppWindow.h \
    Constants.h \
    csv_handler.h \
    ObjectDetector.h \
    recognition_task_consumer.h \
    tasksMutex.h \
    VideoArea.h

CONFIG += thread

CONFIG += link_pkgconfig
PKGCONFIG += gtkmm-3.0
PKGCONFIG += opencv
