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
#ifndef SPACEHARRYSTRUCTS_H
#define SPACEHARRYSTRUCTS_H

class QImage;

struct Bullet
{
  double x = 0.0, y = 0.0, z = 0.0;
  double dX = 0.0, dY = 0.0, dZ = 0.0;
  const QImage * image = nullptr;
};

struct Enemy
{
  double x = 0.0, y = 0.0, z = 0.0;
  int nHitpoints = 1;
  const QImage * image = nullptr;
};

struct Collision
{
  double x = 0.0, y = 0.0, z = 0.0;
  int timeLength = 0; //Time steps to self destruct
  int nTicks = 0;
  const QImage * image = nullptr;
};

struct Sprite
{
  double x = 0.0, y = 0.0, z = 0.0;
  const QImage * image = nullptr;
};

//Sprites furthest away (highest z) are drawn first
inline bool operator<(const Sprite& lhs, const Sprite& rhs) { return lhs.z > rhs.z; }

#endif // SPACEHARRYSTRUCTS_H
