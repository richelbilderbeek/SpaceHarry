# SpaceHarry

[![codecov](https://codecov.io/gh/richelbilderbeek/SpaceHarry/branch/main/graph/badge.svg)](https://codecov.io/gh/richelbilderbeek/SpaceHarry)

The game SpaceHarry, a simple 'Space Harrier' clone, using the C++ Qt library.

- [Go to the nicely rendered website](https://richelbilderbeek.github.io/SpaceHarry/)

Originally written in 2007 using the C++ VCL library.

## Build

Requires Qt 5.10+ or Qt 6 (Widgets module) and a C++17 compiler.

Using CMake:

```text
cmake -S . -B build
cmake --build build
./build/SpaceHarry
```

Using qmake:

```text
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
