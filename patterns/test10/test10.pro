TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    decorator.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    decorator.h

