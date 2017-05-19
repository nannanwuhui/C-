TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    command.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    command.h

