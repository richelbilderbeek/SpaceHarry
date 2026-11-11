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
#include "spaceharrygameoverdialog.h"

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>

#include "spaceharrymenudialog.h" //For CreateCourierFont

SpaceHarryGameOverDialog::SpaceHarryGameOverDialog(QWidget *parent)
  : QDialog(parent, Qt::Dialog | Qt::FramelessWindowHint),
    mCanClose(false)
{
  setWindowTitle("GAME OVER");
  setFixedSize(434, 472);

  QFrame * const panel = new QFrame(this);
  panel->setFrameStyle(QFrame::Panel | QFrame::Raised);
  panel->setLineWidth(5);

  const QFont font = CreateCourierFont(64, true);
  QLabel * const top = new QLabel("GAME OVER", panel);
  top->setFont(font);
  top->setAlignment(Qt::AlignCenter);
  QLabel * const image = new QLabel(panel);
  image->setPixmap(QPixmap(":/game_over.png"));
  image->setAlignment(Qt::AlignCenter);
  QLabel * const bottom = new QLabel("GAME OVER", panel);
  bottom->setFont(font);
  bottom->setAlignment(Qt::AlignCenter);

  QVBoxLayout * const panelLayout = new QVBoxLayout(panel);
  panelLayout->addWidget(top);
  panelLayout->addWidget(image);
  panelLayout->addWidget(bottom);

  QVBoxLayout * const layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(panel);

  QTimer::singleShot(1000, this, [this]() { mCanClose = true; });
}

void SpaceHarryGameOverDialog::keyPressEvent(QKeyEvent *)
{
  if (mCanClose) accept();
}

void SpaceHarryGameOverDialog::mousePressEvent(QMouseEvent *)
{
  if (mCanClose) accept();
}
