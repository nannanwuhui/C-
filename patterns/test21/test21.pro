TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    visitor.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    visitor.h

