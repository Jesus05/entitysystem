TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/engine.cpp \
    engine_test.cpp

HEADERS += \
    ../src/engine.h \
    ../src/debugmacros.h \
    engine_test.h

INCLUDEPATH += ../include ../src

LIBS += -L../lib/ -L../lib/gtest -L../lib/gmock

CONFIG(release, debug|release):LIBS += -lgtest
CONFIG(release, debug|release):LIBS += -lgtest_main

CONFIG(debug, debug|release):LIBS += -lgtestd
CONFIG(debug, debug|release):LIBS += -lgtest_maind
