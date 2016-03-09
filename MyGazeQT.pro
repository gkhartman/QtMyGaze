#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T23:30:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyGazeQT
TEMPLATE = app


SOURCES += main.cpp\
        mygazeqtwidget.cpp

HEADERS  += mygazeqtwidget.h \
    myGazeAPI.h

FORMS    += mygazeqtwidget.ui

QMAKE_CFLAGS += /Gz
QMAKE_CXXFLAGS += /Gz

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lmyGazeAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lmyGazeAPI

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libmyGazeAPI.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libmyGazeAPI.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/myGazeAPI.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/myGazeAPI.lib
