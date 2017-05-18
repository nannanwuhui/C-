TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    composite.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    composite.h

