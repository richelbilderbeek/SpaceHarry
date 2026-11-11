/*
  Space Harry, a simple 'Space Harrier' clone
  Copyright (C) 2007  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// From http://www.richelbilderbeek.nl
#ifndef SPACEHARRYGRAPHICS_H
#define SPACEHARRYGRAPHICS_H

#include <QColor>
#include <QImage>

///Create soil with stripes that widen towards the viewer
QImage CreateSoil(const int width, const int height, const QColor& color1, const QColor& color2);

///Create the lifebar, filled up to 'life' (0.0 = empty, 1.0 = full)
QImage CreateLifebar(const int width, const int height, const double life);

//From http://www.richelbilderbeek.nl/CppRainbow.htm
QColor Rainbow(const double x);
unsigned char GetRed(const double x);
unsigned char GetGreen(const double x);
unsigned char GetBlue(const double x);

#endif // SPACEHARRYGRAPHICS_H
