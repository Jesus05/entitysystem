TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/engine.cpp \
    ../src/system.cpp \
    ../src/entity.cpp \
    ../src/typeindexer.cpp \
    ../src/entitystatemachine.cpp \
    engine_test.cpp \
    system_test.cpp \
    entity_test.cpp \
    speed_test.cpp \
    system_group_test.cpp \
    entitystatemachine_test.cpp

HEADERS += \
    ../src/engine.h \
    ../src/debugmacros.h \
    ../src/system.h \
    ../src/entity.h \
    ../src/entity.hpp \
    ../src/typeindexer.h \
    ../src/systemgroup.h \
    ../src/entitystatemachine.h \
    system_mock.h

INCLUDEPATH += ../include ../src

LIBS += -L../lib/ -L../lib/gtest -L../lib/gmock

#QMAKE_CXXFLAGS -= -O2
#QMAKE_CXXFLAGS += -Ofast
#QMAKE_CXXFLAGS += -Ofast

#QMAKE_LFLAGS -= -O1
#QMAKE_LFLAGS += -Ofast

#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O3

#QMAKE_LFLAGS_RELEASE -= -O1

CONFIG(release, debug|release):LIBS += -lgmock_main
CONFIG(release, debug|release):LIBS += -lgtest
#CONFIG(release, debug|release):LIBS += -lgtest_main
CONFIG(release, debug|release):LIBS += -lgmock


CONFIG(debug, debug|release):LIBS += -lgmock_maind
CONFIG(debug, debug|release):LIBS += -lgtestd
#CONFIG(debug, debug|release):LIBS += -lgtest_maind
CONFIG(debug, debug|release):LIBS += -lgmockd

