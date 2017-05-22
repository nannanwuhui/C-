TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    iterator.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    iterator.h

