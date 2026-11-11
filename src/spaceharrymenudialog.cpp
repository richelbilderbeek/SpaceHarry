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
#include "spaceharrymenudialog.h"

#include <QMouseEvent>
#include <QPainter>

#include "spaceharryaboutdialog.h"
#include "spaceharrygamedialog.h"

QFont CreateCourierFont(const int pixelSize, const bool bold, const bool italic)
{
  QFont font("Courier New");
  font.setStyleHint(QFont::Monospace);
  font.setPixelSize(pixelSize);
  font.setBold(bold);
  font.setItalic(italic);
  return font;
}

SpaceHarryMenuDialog::SpaceHarryMenuDialog(QWidget *parent)
  : QDialog(parent),
    mImageBackground(":/menu_background.png"),
    mImageHarry(":/menu_harry.png"),
    mRectStart(120, 89, 369, 104),
    mRectAbout(8, 192, 241, 62),
    mRectQuit(272, 320, 185, 89)
{
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  setWindowTitle("Space Harry (C) 2007 Richel Bilderbeek");
  setFixedSize(501, 502);
  setMouseTracking(true);
#ifdef Q_OS_WASM
  //The web page is the window: no title bar
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif
}

void SpaceHarryMenuDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(rect(), palette().window());
  painter.drawImage(0, 0, mImageBackground);

  const QFont titleFont = CreateCourierFont(64, true);
  painter.setFont(titleFont);
  painter.setPen(Qt::gray);
  painter.drawText(QRect(38, -3, 418, 73), Qt::AlignHCenter | Qt::AlignTop, "Space Harry");

  painter.drawImage(264, 216, mImageHarry);

  painter.setPen(Qt::black);
  painter.drawText(QRect(0, 0, 501, 73), Qt::AlignHCenter | Qt::AlignTop, "Space Harry");

  painter.setFont(CreateCourierFont(48, true));
  painter.drawText(mRectQuit,  Qt::AlignCenter, "Quit");
  painter.drawText(mRectStart, Qt::AlignCenter, "Start Game");
  painter.drawText(mRectAbout, Qt::AlignCenter, "About");
}

void SpaceHarryMenuDialog::mouseMoveEvent(QMouseEvent *event)
{
  const QPoint p = event->pos();
  const bool isOverButton
    = mRectStart.contains(p) || mRectAbout.contains(p) || mRectQuit.contains(p);
  setCursor(isOverButton ? Qt::PointingHandCursor : Qt::ArrowCursor);
}

void SpaceHarryMenuDialog::mousePressEvent(QMouseEvent *event)
{
  if (event->button() != Qt::LeftButton) return;
  const QPoint p = event->pos();
  if (mRectStart.contains(p)) OnStart();
  else if (mRectAbout.contains(p)) OnAbout();
  else if (mRectQuit.contains(p)) close();
}

//Dialogs are opened without QDialog::exec, as a nested event loop
//is not supported by Qt for WebAssembly
void SpaceHarryMenuDialog::OnStart()
{
  SpaceHarryGameDialog * const d = new SpaceHarryGameDialog(this);
  d->setAttribute(Qt::WA_DeleteOnClose);
  d->open();
}

void SpaceHarryMenuDialog::OnAbout()
{
  SpaceHarryAboutDialog * const d = new SpaceHarryAboutDialog(this);
  d->setAttribute(Qt::WA_DeleteOnClose);
  d->open();
}
