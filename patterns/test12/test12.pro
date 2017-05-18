TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    templatemethod.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    templatemethod.h

