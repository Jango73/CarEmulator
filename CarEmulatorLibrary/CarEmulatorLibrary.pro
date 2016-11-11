#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T15:40:48
#
#-------------------------------------------------

QT += core gui xml network serialport widgets positioning qml quickwidgets

CONFIG += warn_off

TARGET = CarEmulatorLibrary
TEMPLATE = lib

DEFINES += CAREMULATOR_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    Source/CarEmulatorGlobal.h \
    Source/CUtils.h \
    Source/CInterpolator.h \
    Source/CNormalizedInput.h \
    Source/CSensorValue.h \
    Source/CSensors.h \
    Source/CEngineSettings.h \
    Source/CCarSettings.h \
    Source/CGearBox.h \
    Source/CCar.h \
    Source/CCarEmulator.h

SOURCES += \
    Source/CNormalizedInput.cpp \
    Source/CSensorValue.cpp \
    Source/CSensors.cpp \
    Source/CEngineSettings.cpp \
    Source/CCarSettings.cpp \
    Source/CGearBox.cpp \
    Source/CCar.cpp \
    Source/CCarEmulator.cpp
