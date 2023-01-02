QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    absurdroundwindow.cpp \
    absurdwordleround.cpp \
    dictionary.cpp \
    key.cpp \
    keyboard.cpp \
    letterbox.cpp \
    main.cpp \
    mainwindow.cpp \
    multiroundwindow.cpp \
    multiwordleround.cpp \
    regularroundwindow.cpp \
    regularwordleround.cpp \
    roundwindow.cpp \
    solver.cpp \
    timedroundwindow.cpp \
    timedwordleround.cpp \
    wordleround.cpp

HEADERS += \
    absurdroundwindow.h \
    absurdwordleround.h \
    dictionary.h \
    helper.h \
    key.h \
    keyboard.h \
    letterbox.h \
    mainwindow.h \
    multiroundwindow.h \
    multiwordleround.h \
    regularroundwindow.h \
    regularwordleround.h \
    roundwindow.h \
    solver.h \
    timedroundwindow.h \
    timedwordleround.h \
    wordleround.h

FORMS += \
    mainwindow.ui \
    roundwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
