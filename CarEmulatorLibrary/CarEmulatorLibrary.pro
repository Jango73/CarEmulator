#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T15:40:48
#
#-------------------------------------------------

QT += core multimedia qml quick

CONFIG += warn_off
CONFIG += qt plugin
CONFIG += c++11

TARGET = CarEmulatorLibrary
TEMPLATE = lib

DEFINES += CAREMULATOR_LIBRARY

# unix {
#     target.path = /usr/lib
#     INSTALLS += target
# }

HEADERS += \
    Source/CarEmulatorGlobal.h \
    Source/CUtils.h \
    Source/CInterpolator.h \
    Source/CAverager.h \
    Source/CPIDController.h \
    Source/CNormalizedInput.h \
    Source/CSensorValue.h \
    Source/CSensorBooleanValue.h \
    Source/CSensorIntegerValue.h \
    Source/CSensorRealValue.h \
    Source/CSensors.h \
    Source/CEngineSettings.h \
    Source/CCarSettings.h \
    Source/CGearBox.h \
    Source/CSoundSynth.h \
    Source/CEngineSound.h \
    Source/CCar.h \
    Source/CCarAI.h \
    Source/CarEmulatorPlugin.h

SOURCES += \
    Source/CPIDController.cpp \
    Source/CNormalizedInput.cpp \
    Source/CSensorValue.cpp \
    Source/CSensorBooleanValue.cpp \
    Source/CSensorIntegerValue.cpp \
    Source/CSensorRealValue.cpp \
    Source/CSensors.cpp \
    Source/CEngineSettings.cpp \
    Source/CCarSettings.cpp \
    Source/CGearBox.cpp \
    Source/CSoundSynth.cpp \
    Source/CEngineSound.cpp \
    Source/CCar.cpp \
    Source/CCarAI.cpp \
    Source/CarEmulatorPlugin.cpp

# Install directives

!include(Source/MODULE): error(MODULE File is missing !! Please create one !!)
isEmpty(URI): error("No URI defined, please set the URI variable")
isEmpty(VERSION_MAJOR): error("Major version number missing, please set the VERSION_MAJOR variable in the VERSION file")
isEmpty(VERSION_MINOR): error("Minor version number missing, please set the VERSION_MINOR variable in the VERSION file")
isEmpty(REVISION): error("Revision name missing, please set the REVISION variable in the VERSION file")

MODULE_ID = $$replace(URI, \\., -)
MODULE_VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}
FULL_MODULE_VERSION = $${MODULE_VERSION}.$${REVISION}
MODULE_PATH = $$replace(URI, \\., /)

unix {
PATH_TO_TARGET = $${OUT_PWD}/release/$${TARGET}.so
}

win32 {
PATH_TO_TARGET = $${OUT_PWD}/release/$${TARGET}.dll
}

DEFINES += URI=\\\"$$URI\\\"
DEFINES += VERSION_MAJOR=$$VERSION_MAJOR
DEFINES += VERSION_MINOR=$$VERSION_MINOR
DEFINES += MODULE_ID=$$MODULE_ID
DEFINES += MODULE_PATH=\\\"$$MODULE_PATH\\\"

isEmpty(INSTALL_DIR): INSTALL_DIR = $$[QT_INSTALL_QML]

INSTALL_PATH = $${INSTALL_DIR}/$${MODULE_PATH}

module.files = Source/qmldir $${PATH_TO_TARGET}
module.path = $${INSTALL_PATH}

# install once if release & debug are both build
# !build_all|CONFIG(release, debug|release): INSTALLS += module
INSTALLS += module

!build_pass {
    message(Qt version: $$[QT_VERSION])
    message(Module ID: $${MODULE_ID})
    message(Module URI: $${URI})
    message(Module version: $${FULL_MODULE_VERSION})
    message(Install path: $${INSTALL_PATH})
    message(Path to target: $${PATH_TO_TARGET})
}
