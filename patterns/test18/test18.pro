TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    state.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    state.h

