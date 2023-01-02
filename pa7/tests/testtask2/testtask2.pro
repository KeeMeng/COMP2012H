QT += testlib widgets core gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testtask2.cpp

HEADERS +=  tst_testtask2.h

APPDIR = ../../app

INCLUDEPATH += $$APPDIR

SOURCES += \
    $$APPDIR/dictionary.cpp \
    $$APPDIR/key.cpp \
    $$APPDIR/keyboard.cpp \
    $$APPDIR/letterbox.cpp \
    $$APPDIR/regularroundwindow.cpp \
    $$APPDIR/regularwordleround.cpp \
    $$APPDIR/roundwindow.cpp \
    $$APPDIR/solver.cpp \
    $$APPDIR/wordleround.cpp

HEADERS += \
    $$APPDIR/dictionary.h \
    $$APPDIR/helper.h \
    $$APPDIR/key.h \
    $$APPDIR/keyboard.h \
    $$APPDIR/letterbox.h \
    $$APPDIR/regularroundwindow.h \
    $$APPDIR/regularwordleround.h \
    $$APPDIR/roundwindow.h \
    $$APPDIR/solver.h \
    $$APPDIR/wordleround.h

FORMS += \
    $$APPDIR/mainwindow.ui \
    $$APPDIR/roundwindow.ui

RESOURCES += \
    $$APPDIR/resource.qrc
