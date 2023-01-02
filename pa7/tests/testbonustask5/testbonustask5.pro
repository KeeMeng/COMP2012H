QT += testlib widgets core gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testbonustask5.cpp

HEADERS +=  tst_testbonustask5.h

APPDIR = ../../app

INCLUDEPATH += $$APPDIR

SOURCES += \
    $$APPDIR/dictionary.cpp

HEADERS += \
    $$APPDIR/dictionary.h

RESOURCES += \
    $$APPDIR/resource.qrc
