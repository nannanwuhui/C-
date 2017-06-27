TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += debug
DEFINES += DEBUG

SOURCES += main.cpp

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
