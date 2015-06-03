#-------------------------------------------------
#
# Project created by QtCreator 2011-05-14T15:37:51
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArenaControl
TEMPLATE = app


SOURCES += \
    src/main.cpp\
    src/timer.cpp \
    src/startstopbutton.cpp \
    src/timesetter.cpp \
    src/controllights.cpp \
    src/buttons.cpp \
    src/k8055usbboard.cpp \
    src/robot.cpp \
    src/team.cpp \
    src/audiencescreen.cpp \
    src/arenacontrol.cpp \
    src/serialcontrolboard.cpp \
    src/ccrsmallarena.cpp

HEADERS  += \
    include/timer.h \
    include/startstopbutton.h \
    include/timesetter.h \
    include/controllights.h \
    include/buttons.h \
    include/k8055usbboard.h \
    include/robot.h \
    include/team.h \
    include/audiencescreen.h \
    include/arenacontrol.h \
    include/controlboardinterface.h \
    include/serialcontrolboard.h \
    include/arenaInterface.h \
    include/ccrsmallarena.h

FORMS    += \
    forms/arenacontrol.ui \
    forms/audiencescreen.ui

RESOURCES += \
    resources/controlResources.qrc

INCLUDEPATH += \
    include

install_libs.path = $$OUT_PWD/lib
install_libs.files += lib/k8055.dll

INSTALLS += install_libs
