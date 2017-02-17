TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    engine.cpp \
    system.cpp \
    entity.cpp

HEADERS += \
    engine.h \
    debugmacros.h \
    system.h \
    entity.h \
    entity.hpp

QMAKE_LFLAGS += -Wl,-Map=myfile.map
