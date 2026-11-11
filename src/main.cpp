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
#include <QApplication>
#include <QScreen>

#include "spaceharrymenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setApplicationName("Space Harry");
  SpaceHarryMenuDialog w;
#ifdef Q_OS_WASM
  //Put the menu in the middle of the web page
  const QRect screen = w.screen()->availableGeometry();
  w.move(
    screen.x() + (screen.width()  - w.width())  / 2,
    screen.y() + (screen.height() - w.height()) / 2);
#endif
  w.show();
  return a.exec();
}
