win32:msvc {
  CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += /EHsc /D_DEBUG /MDd
    QMAKE_LFLAGS += /WX
  } else {
    QMAKE_CXXFLAGS += /O2 /EHsc /DNDEBUG /MD
    QMAKE_LFLAGS += /WX
  }
}

win32:mingw {
  QMAKE_CXXFLAGS += -g -O3 -std=c++14
  QMAKE_LFLAGS += --static -Wl,--no-undefined -static-libgcc -static-libstdc++
}
