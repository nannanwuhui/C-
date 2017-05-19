TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    flyweight.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    flyweight.h

