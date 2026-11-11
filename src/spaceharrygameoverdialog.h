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
#ifndef SPACEHARRYGAMEOVERDIALOG_H
#define SPACEHARRYGAMEOVERDIALOG_H

#include <QDialog>

///Shown when Harry has died. Can be closed by a key or mouse press
///after one second, so the player does not close it by accident
class SpaceHarryGameOverDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SpaceHarryGameOverDialog(QWidget *parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

private:
  bool mCanClose;
};

#endif // SPACEHARRYGAMEOVERDIALOG_H
