TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

include(..\third\flags.pri)

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

INCLUDEPATH += \
  ../include \
  ../src \
  ../third/third_googletest/googletest/googlemock/include \
  ../third/third_googletest/googletest/googletest/include

LIBS += -L../lib/ -L../third/lib

#QMAKE_CXXFLAGS -= -O2
#QMAKE_CXXFLAGS += -Ofast
#QMAKE_CXXFLAGS += -Ofast

#QMAKE_LFLAGS -= -O1
#QMAKE_LFLAGS += -Ofast

#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O3

#QMAKE_LFLAGS_RELEASE -= -O1

CONFIG(debug, debug|release):LIBS += -lgtestmock
CONFIG(debug, debug|release):LIBS += -lgtestmockd

