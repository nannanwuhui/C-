TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    memento.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    memento.h

