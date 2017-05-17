TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += DEBUG
CONFIG += debug
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x
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
    prototype.h

SOURCES += \
    prototype.cpp \
    main.cpp
