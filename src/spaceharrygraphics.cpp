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
#include "spaceharrygraphics.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace {
  const double pi = 3.14159265358979323846;
}

QImage CreateSoil(const int width, const int height, const QColor& color1, const QColor& color2)
{
  QImage image(std::max(1, width), std::max(1, height), QImage::Format_RGB32);
  bool use1 = true;
  for (int y = 0; y != image.height(); ++y)
  {
    const int sqrtY = static_cast<int>(std::sqrt(static_cast<double>(y)) + 0.5);
    if (sqrtY * sqrtY == y) use1 = !use1;
    const QRgb c = (use1 ? color1 : color2).rgb();
    QRgb * const line = reinterpret_cast<QRgb*>(image.scanLine(y));
    std::fill(line, line + image.width(), c);
  }
  return image;
}

QImage CreateLifebar(const int width, const int height, const double life)
{
  QImage image(std::max(1, width), std::max(1, height), QImage::Format_RGB32);
  const int w = image.width();
  const int h = image.height();
  //Grey gradient border
  for (int y = 0; y != h; ++y)
  {
    const int grey = static_cast<int>(256.0 * static_cast<double>(y) / static_cast<double>(h));
    assert(grey >= 0 && grey < 256);
    QRgb * const line = reinterpret_cast<QRgb*>(image.scanLine(y));
    std::fill(line, line + w, qRgb(grey, grey, grey));
  }
  //Rainbow-colored inside, black where life is lost
  const int quarterWidth = w / 4;
  const int heightLeft = h - quarterWidth - quarterWidth;
  if (heightLeft <= 0) return image;
  for (int y = quarterWidth; y != h - quarterWidth; ++y)
  {
    const double fraction
      = static_cast<double>(y - quarterWidth) / static_cast<double>(heightLeft);
    const QRgb c = (1.0 - fraction > life) ? qRgb(0, 0, 0) : Rainbow(fraction).rgb();
    QRgb * const line = reinterpret_cast<QRgb*>(image.scanLine(y));
    std::fill(line + quarterWidth, line + w - quarterWidth, c);
  }
  return image;
}

QColor Rainbow(const double x)
{
  const int r0 = GetRed(x);
  const int g0 = GetGreen(x);
  const int b0 = GetBlue(x);
  const int max = std::max(r0, std::max(g0, b0));
  assert(max != 0);
  return QColor(
    static_cast<int>(255.0 * r0 / max),
    static_cast<int>(255.0 * g0 / max),
    static_cast<int>(255.0 * b0 / max));
}

unsigned char GetRed(const double x)
{
  assert(x >= 0.0 && x < 1.0);
  const double f = std::max(0.0,
    (x < 0.5 ? std::cos(x * 1.5 * pi) : -std::sin(x * 1.5 * pi)));
  assert(f >= 0.0 && f <= 1.0);
  return static_cast<unsigned char>(255.0 * f);
}

unsigned char GetGreen(const double x)
{
  assert(x >= 0.0 && x < 1.0);
  const double f = std::max(0.0, std::sin(x * 1.5 * pi));
  assert(f >= 0.0 && f <= 1.0);
  return static_cast<unsigned char>(255.0 * f);
}

unsigned char GetBlue(const double x)
{
  assert(x >= 0.0 && x < 1.0);
  const double f = std::max(0.0, -std::cos(x * 1.5 * pi));
  assert(f >= 0.0 && f <= 1.0);
  return static_cast<unsigned char>(255.0 * f);
}
