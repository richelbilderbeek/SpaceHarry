# SpaceHarry

Branch|[![Travis CI logo](pics/TravisCI.png)](https://travis-ci.org)
---|---
`master`|[![Build Status](https://travis-ci.org/richelbilderbeek/SpaceHarry.svg?branch=master)](https://travis-ci.org/richelbilderbeek/SpaceHarry)

The game SpaceHarry, a simple 'Space Harrier' clone, using the C++ Qt library.

Originally written in 2007 using the C++ VCL library.

## Build

Requires Qt 5.10+ or Qt 6 (Widgets module) and a C++17 compiler.

Using CMake:

```
cmake -S . -B build
cmake --build build
./build/SpaceHarry
```

Using qmake:

```
qmake SpaceHarry.pro
make
./SpaceHarry
```

## Controls

Key|Action
---|---
Arrow keys|Move Harry
Space|Shoot
F1|Toggle transparent Harry
Escape|Quit the game
