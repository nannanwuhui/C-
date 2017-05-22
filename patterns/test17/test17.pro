TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    strategy.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    strategy.h

