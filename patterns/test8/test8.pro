TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bridge.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    bridge.h

