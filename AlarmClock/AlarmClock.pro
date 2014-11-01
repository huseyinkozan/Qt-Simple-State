#-------------------------------------------------
#
# Project created by QtCreator 2014-11-01T00:27:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlarmClock
TEMPLATE = app

Qt_S_S = $$PWD/../state
include($$Qt_S_S/state.pri)


SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS  += \
    MainWindow.h \
    States/Alarm.h \
    States/Mode.h

FORMS    += MainWindow.ui
