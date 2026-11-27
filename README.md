# SpaceHarry

<!-- markdownlint-disable MD013 --><!-- Badges cannot be split up over lines, hence will break 80 characters per line -->

[![Check build](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_build.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_build.yaml)
[![check_links](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_links.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_links.yaml)
[![Check Markdown](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_markdown.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_markdown.yaml)
[![Check spelling](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_spelling.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/check_spelling.yaml)
[![codecov](https://codecov.io/gh/richelbilderbeek/SpaceHarry/branch/main/graph/badge.svg)](https://codecov.io/gh/richelbilderbeek/SpaceHarry)
[![Create Zensical website](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/create_zensical_website.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/SpaceHarry/actions/workflows/create_zensical_website.yaml)

<!-- markdownlint-enable MD013 -->

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
