TEMPLATE = lib
CONFIG += c++20
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

SOURCES += main.cpp \
    engine.cpp \
    helpers.cpp \
    system.cpp \
    entity.cpp \
    typeindexer.cpp \
    entitystatemachine.cpp

HEADERS += \
    engine.h \
    debugmacros.h \
    helpers.h \
    system.h \
    entity.h \
    entity.hpp \
    typeindexer.h \
    systemgroup.h \
    entitystatemachine.h

QMAKE_LFLAGS += -Wl,-Map=myfile.map

DESTDIR = ..\lib\

android {
    CONFIG(release, debug|release):TARGET = entitysystemandroid

    CONFIG(debug, debug|release):TARGET = entitysystemandroidd
}

win32 {
    CONFIG(release, debug|release):TARGET = entitysystem

    CONFIG(debug, debug|release):TARGET = entitysystemd
}
