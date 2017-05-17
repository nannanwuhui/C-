TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    adapt.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    adapt.h

