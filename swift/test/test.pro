TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

BASEDIR = /home/backup/develop/x86_64/debug/
INCLUDEPATH += \
                $$BASEDIR/include \
                $$BASEDIR/include/libxml2
LIBS += \
    -L $$BASEDIR/lib/
LIBS += \
    -lswift-1.0.0-gcc -ltea -lxml2 -ledklib
QMAKE_RPATHDIR += $$BASEDIR/lib
