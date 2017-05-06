TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += DEBUG
CONFIG += debug
SOURCES += main.cpp \
    network.cpp

include(deployment.pri)
qtcAddDeployment()


BASEDIR = /home/backup/develop/x86_64/debug
INCLUDEPATH += \
        $$BASEDIR/include \
        $$BASEDIR/include/libxml2/

LIBS += \
    -L $$BASEDIR/lib/

LIBS += \
        -lboost_system -lboost_thread -lpthread -ledklib
QMAKE_RPATHDIR += $$BASEDIR/lib

HEADERS += \
    network.h

