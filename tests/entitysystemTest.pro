TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/engine.cpp \
    ../src/system.cpp \
    ../src/entity.cpp \
    engine_test.cpp \
    system_test.cpp \
    entety_test.cpp

HEADERS += \
    ../src/engine.h \
    ../src/debugmacros.h \
    ../src/system.h \
    ../src/entity.h \
    ../src/entity.hpp \
    system_mock.h

INCLUDEPATH += ../include ../src

LIBS += -L../lib/ -L../lib/gtest -L../lib/gmock

CONFIG(release, debug|release):LIBS += -lgmock_main
CONFIG(release, debug|release):LIBS += -lgtest
CONFIG(release, debug|release):LIBS += -lgtest_main
CONFIG(release, debug|release):LIBS += -lgmock


CONFIG(debug, debug|release):LIBS += -lgmock_maind
CONFIG(debug, debug|release):LIBS += -lgtestd
CONFIG(debug, debug|release):LIBS += -lgtest_maind
CONFIG(debug, debug|release):LIBS += -lgmockd

