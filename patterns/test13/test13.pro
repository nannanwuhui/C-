TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    chainofresponsibility.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    chainofresponsibility.h

