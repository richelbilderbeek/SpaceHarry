# Tests for the game, with code coverage measured in CI
# Run with: ./spaceharry_test

QT += core gui widgets
CONFIG += c++17
TARGET = spaceharry_test
TEMPLATE = app

SOURCES += \
  spaceharry_test.cpp \
  src/spaceharryaboutdialog.cpp \
  src/spaceharrygamedialog.cpp \
  src/spaceharrygameoverdialog.cpp \
  src/spaceharrygraphics.cpp \
  src/spaceharrymenudialog.cpp

HEADERS += \
  src/spaceharryaboutdialog.h \
  src/spaceharrygamedialog.h \
  src/spaceharrygameoverdialog.h \
  src/spaceharrygraphics.h \
  src/spaceharrymenudialog.h \
  src/spaceharrystructs.h

RESOURCES += resources/spaceharry.qrc

QT += testlib
CONFIG += console
CONFIG -= app_bundle
