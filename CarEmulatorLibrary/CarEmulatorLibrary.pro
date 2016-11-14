#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T15:40:48
#
#-------------------------------------------------

QT += core multimedia

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
    Source/CSensorBooleanValue.h \
    Source/CSensorRealValue.h \
    Source/CSensors.h \
    Source/CEngineSettings.h \
    Source/CCarSettings.h \
    Source/CGearBox.h \
    Source/CSoundSynth.h \
    Source/CEngineSound.h \
    Source/CCar.h

SOURCES += \
    Source/CNormalizedInput.cpp \
    Source/CSensorBooleanValue.cpp \
    Source/CSensorRealValue.cpp \
    Source/CSensors.cpp \
    Source/CEngineSettings.cpp \
    Source/CCarSettings.cpp \
    Source/CGearBox.cpp \
    Source/CSoundSynth.cpp \
    Source/CEngineSound.cpp \
    Source/CCar.cpp
