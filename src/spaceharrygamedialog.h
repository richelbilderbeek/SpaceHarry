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
#ifndef SPACEHARRYGAMEDIALOG_H
#define SPACEHARRYGAMEDIALOG_H

#include <set>
#include <vector>

#include <QDialog>
#include <QImage>
#include <QTimer>

#include "spaceharrystructs.h"

class SpaceHarryGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SpaceHarryGameDialog(QWidget *parent = nullptr);

  int GetScore() const noexcept { return mScore; }

protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

private slots:
  void OnGameTimer();
  void OnKeyPressTimer();

private:
  //Sprites
  const QImage mImageHarry;
  const QImage mImageHarryTransparent;
  const QImage mImageBulletHarry;
  const QImage mImageBulletBlue;
  const QImage mImageEnemySkull;
  const QImage mImageCollisionBlue;
  const QImage mImageCollisionGreen;

  //Backgrounds, recreated when resized
  QImage mImageSoil1;
  QImage mImageSoil2;
  QImage mImageLifebar;

  QTimer mTimerGame;
  QTimer mTimerKeyPress;

  double mX, mY, mZ; //Harry's coordinats
  int mScore;
  bool mIsHarryTransparent;
  bool mIsHarryPlaced;
  bool mDrawSoil1;
  double mLife;
  std::vector<Bullet> mBullets;
  std::vector<Enemy> mEnemies;
  std::vector<Collision> mCollisions;
  std::set<int> mKeys;

  void DrawNewLifebar();
  void GameOver();
  void UpdateTitle();
};

#endif // SPACEHARRYGAMEDIALOG_H
