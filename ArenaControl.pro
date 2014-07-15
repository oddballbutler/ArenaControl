#-------------------------------------------------
#
# Project created by QtCreator 2011-05-14T15:37:51
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArenaControl
TEMPLATE = app


SOURCES += main.cpp\
    timer.cpp \
    startstopbutton.cpp \
    timesetter.cpp \
    controllights.cpp \
    buttons.cpp \
    k8055usbboard.cpp \
    robot.cpp \
    team.cpp \
    audiencescreen.cpp \
    arenacontrol.cpp

HEADERS  += \
    timer.h \
    startstopbutton.h \
    timesetter.h \
    controllights.h \
    buttons.h \
    k8055usbboard.h \
    robot.h \
    team.h \
    audiencescreen.h \
    arenacontrol.h

FORMS    += arenacontrol.ui \
    audiencescreen.ui

RESOURCES += \
    controlResources.qrc
