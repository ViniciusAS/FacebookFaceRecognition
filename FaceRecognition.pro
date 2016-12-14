TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    recognizedfacerow.cpp \
    recognizedfaceslist.cpp \
    videoarea.cpp \
    objectdetector.cpp \
    facerecognizer.cpp \
    facerecognitionqueue.cpp \
    appwindow.cpp

DISTFILES += \
    installOpenCV_latest.sh \
    faces.csv \
    labels.csv \
    .gitignore

HEADERS += \
    csv_handler.h \
    recognition_task_consumer.h \
    recognizedfacerow.h \
    videoarea.h \
    recognizedfaceslist.h \
    tasksmutex.h \
    objectdetector.h \
    facerecognizer.h \
    facerecognitionqueue.h \
    constants.h \
    appwindow.h

CONFIG += thread

CONFIG += link_pkgconfig
PKGCONFIG += gtkmm-3.0
PKGCONFIG += opencv
