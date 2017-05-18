TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    proxy.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    proxy.h

