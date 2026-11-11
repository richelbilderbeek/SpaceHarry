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
#ifndef SPACEHARRYMENUDIALOG_H
#define SPACEHARRYMENUDIALOG_H

#include <QDialog>
#include <QImage>
#include <QRect>

class SpaceHarryMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SpaceHarryMenuDialog(QWidget *parent = nullptr);

protected:
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  const QImage mImageBackground;
  const QImage mImageHarry;
  const QRect mRectStart;
  const QRect mRectAbout;
  const QRect mRectQuit;

  void OnStart();
  void OnAbout();
};

///Courier New with a monospace fallback, sized in pixels like VCL's Font.Height
QFont CreateCourierFont(const int pixelSize, const bool bold, const bool italic = false);

#endif // SPACEHARRYMENUDIALOG_H
