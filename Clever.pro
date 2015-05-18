TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    matrix.cpp \
    perceptron.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    matrix.h \
    perceptron.h

