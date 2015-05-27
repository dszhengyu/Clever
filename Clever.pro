TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    matrix.cpp \
    perceptron.cpp \
    knn.cpp \
    kdtree.cpp \
    naivebayes.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    matrix.h \
    perceptron.h \
    knn.h \
    kdtree.h \
    naivebayes.h

