#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T19:47:08
#
#-------------------------------------------------

QT += core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarEmulatorApp
TEMPLATE = app

SOURCES += \
    main.cpp \
    CMainWindow.cpp

HEADERS  += \
    CMainWindow.h

FORMS    += CMainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CarEmulatorLibrary/release/ -lCarEmulatorLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CarEmulatorLibrary/debug/ -lCarEmulatorLibrary
else:unix: LIBS += -L$$OUT_PWD/../CarEmulatorLibrary/ -lCarEmulatorLibrary

INCLUDEPATH += $$PWD/../CarEmulatorLibrary
DEPENDPATH += $$PWD/../CarEmulatorLibrary

RESOURCES += \
    Resources/CarEmulatorApp.qrc
