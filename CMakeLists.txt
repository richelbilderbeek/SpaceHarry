cmake_minimum_required(VERSION 3.16)
project(SpaceHarry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(SpaceHarry
  src/main.cpp
  src/spaceharryaboutdialog.cpp
  src/spaceharryaboutdialog.h
  src/spaceharrygamedialog.cpp
  src/spaceharrygamedialog.h
  src/spaceharrygameoverdialog.cpp
  src/spaceharrygameoverdialog.h
  src/spaceharrymenudialog.cpp
  src/spaceharrymenudialog.h
  src/spaceharrystructs.h
  src/spaceharrygraphics.cpp
  src/spaceharrygraphics.h
  resources/spaceharry.qrc
)

target_link_libraries(SpaceHarry PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(MSVC)
  target_compile_options(SpaceHarry PRIVATE /W4)
else()
  target_compile_options(SpaceHarry PRIVATE -Wall -Wextra -Wpedantic)
endif()
