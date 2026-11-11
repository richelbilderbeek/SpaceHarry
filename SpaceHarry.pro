QT += core gui widgets
CONFIG += c++17
TARGET = SpaceHarry
TEMPLATE = app

SOURCES += \
  src/main.cpp \
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
