TEMPLATE = lib
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

SOURCES += main.cpp \
    engine.cpp \
    system.cpp \
    entity.cpp \
    typeindexer.cpp \
    entitystatemachine.cpp

HEADERS += \
    engine.h \
    debugmacros.h \
    system.h \
    entity.h \
    entity.hpp \
    typeindexer.h \
    systemgroup.h \
    entitystatemachine.h

QMAKE_LFLAGS += -Wl,-Map=myfile.map

CONFIG(debug, debug|release):TARGET = entitysystemd

DESTDIR = ..\lib\
