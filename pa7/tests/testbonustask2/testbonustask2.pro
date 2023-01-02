QT += testlib widgets core gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testbonustask2.cpp

HEADERS +=  tst_testbonustask2.h

APPDIR = ../../app

INCLUDEPATH += $$APPDIR

SOURCES += \
    $$APPDIR/absurdroundwindow.cpp \
    $$APPDIR/absurdwordleround.cpp \
    $$APPDIR/dictionary.cpp \
    $$APPDIR/key.cpp \
    $$APPDIR/keyboard.cpp \
    $$APPDIR/letterbox.cpp \
    $$APPDIR/mainwindow.cpp \
    $$APPDIR/multiroundwindow.cpp \
    $$APPDIR/multiwordleround.cpp \
    $$APPDIR/regularroundwindow.cpp \
    $$APPDIR/regularwordleround.cpp \
    $$APPDIR/roundwindow.cpp \
    $$APPDIR/solver.cpp \
    $$APPDIR/timedroundwindow.cpp \
    $$APPDIR/timedwordleround.cpp \
    $$APPDIR/wordleround.cpp

HEADERS += \
    $$APPDIR/absurdroundwindow.h \
    $$APPDIR/absurdwordleround.h \
    $$APPDIR/dictionary.h \
    $$APPDIR/helper.h \
    $$APPDIR/key.h \
    $$APPDIR/keyboard.h \
    $$APPDIR/letterbox.h \
    $$APPDIR/mainwindow.h \
    $$APPDIR/multiroundwindow.h \
    $$APPDIR/multiwordleround.h \
    $$APPDIR/regularroundwindow.h \
    $$APPDIR/regularwordleround.h \
    $$APPDIR/roundwindow.h \
    $$APPDIR/solver.h \
    $$APPDIR/timedroundwindow.h \
    $$APPDIR/timedwordleround.h \
    $$APPDIR/wordleround.h

FORMS += \
    $$APPDIR/mainwindow.ui \
    $$APPDIR/roundwindow.ui

RESOURCES += \
    $$APPDIR/resource.qrc
