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
#include "spaceharrygamedialog.h"

#include <algorithm>

#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>

#include "spaceharrygameoverdialog.h"
#include "spaceharrygraphics.h"

namespace {
  const int lifebarWidth = 20;

  int RandomBelow(const int n)
  {
    return n > 0 ? QRandomGenerator::global()->bounded(n) : 0;
  }
}

SpaceHarryGameDialog::SpaceHarryGameDialog(QWidget *parent)
  : QDialog(parent),
    mImageHarry(":/harry.png"),
    mImageHarryTransparent(":/harry_transparent.png"),
    mImageBulletHarry(":/bullet_harry.png"),
    mImageBulletBlue(":/bullet_blue.png"),
    mImageEnemySkull(":/enemy_skull.png"),
    mImageCollisionBlue(":/collision_blue.png"),
    mImageCollisionGreen(":/collision_green.png"),
    mX(0.0), mY(0.0), mZ(0.0),
    mScore(0),
    mIsHarryTransparent(false),
    mIsHarryPlaced(false),
    mDrawSoil1(true),
    mLife(1.0)
{
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
#ifdef Q_OS_WASM
  //The web page is the window: no title bar
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif
  setFocusPolicy(Qt::StrongFocus);
  setMinimumSize(491, 452);
  setWindowState(Qt::WindowMaximized);
  UpdateTitle();

  connect(&mTimerGame, &QTimer::timeout, this, &SpaceHarryGameDialog::OnGameTimer);
  connect(&mTimerKeyPress, &QTimer::timeout, this, &SpaceHarryGameDialog::OnKeyPressTimer);
  mTimerGame.start(50);
  mTimerKeyPress.start(20);
}

void SpaceHarryGameDialog::UpdateTitle()
{
  setWindowTitle(
    QString("Space Harry (C) 2007 Richel Bilderbeek. Score: %1").arg(mScore));
}

void SpaceHarryGameDialog::resizeEvent(QResizeEvent *event)
{
  QDialog::resizeEvent(event);
  const int skyHeight = height() / 2;
  const int soilHeight = height() - skyHeight;
  mImageSoil1 = CreateSoil(width(), soilHeight, QColor(0, 255, 0), QColor(0, 128, 0));
  mImageSoil2 = CreateSoil(width(), soilHeight, QColor(0, 128, 0), QColor(0, 255, 0));
  DrawNewLifebar();
  if (!mIsHarryPlaced)
  {
    mX = width() / 2;
    mY = height() / 2;
    mIsHarryPlaced = true;
  }
  update();
}

void SpaceHarryGameDialog::DrawNewLifebar()
{
  mImageLifebar = CreateLifebar(lifebarWidth, height(), mLife);
}

void SpaceHarryGameDialog::OnGameTimer()
{
  const int w = width();
  const int h = height();

  //Spawn a new wave of enemies
  if (mEnemies.empty())
  {
    for (int i = 0; i != 5; ++i)
    {
      Enemy e;
      e.x = RandomBelow(w);
      e.y = RandomBelow(h);
      e.z = 1.0;
      e.nHitpoints = 2;
      e.image = &mImageEnemySkull;
      mEnemies.push_back(e);
    }
  }

  //Age collisions
  for (Collision& c : mCollisions) ++c.nTicks;
  mCollisions.erase(
    std::remove_if(mCollisions.begin(), mCollisions.end(),
      [](const Collision& c) { return c.nTicks >= c.timeLength; }),
    mCollisions.end());

  //Move enemies
  for (Enemy& e : mEnemies)
  {
    if (e.z > 0.5) e.z -= 0.01; //Move enemy forward

    const int iw = e.image->width();
    const int ih = e.image->height();
    if (e.x < w / 2)
    {
      if (e.y < h / 2)
      {
        if (e.x > -iw) e.x -= 10;
        e.y += 10;
      }
      else
      {
        if (e.y < h - ih) e.y += 10;
        e.x += 10;
      }
    }
    else
    {
      if (e.y < h / 2)
      {
        if (e.y > -ih) e.y -= 10;
        e.x -= 10;
      }
      else
      {
        if (e.x < w - iw) e.x += 10;
        e.y -= 10;
      }
    }

    if (RandomBelow(25) == 0)
    {
      //Enemy fires bullet!
      Bullet b;
      b.x = e.x;
      b.y = e.y;
      b.z = e.z - 0.0501;
      b.dZ = -0.05;
      b.dX = b.dZ * ((w / 2.0) - b.x);
      b.dY = b.dZ * ((h / 2.0) - b.y);
      b.image = &mImageBulletBlue;
      mBullets.push_back(b);
    }
  }

  //Move bullets and check for hits
  std::vector<Bullet> survivors;
  survivors.reserve(mBullets.size());
  for (Bullet b : mBullets)
  {
    b.x += b.dX;
    b.y += b.dY;
    b.z += b.dZ;
    //Remove bullet if out of screen
    if (b.z < -1.0 || b.z > 0.6) continue;

    //Check if bullet hit Harry
    const double harryHalfWidth  = mImageHarry.width()  / 2.0;
    const double harryHalfHeight = mImageHarry.height() / 2.0;
    if (b.x > mX - harryHalfWidth  && b.x < mX + harryHalfWidth
     && b.y > mY - harryHalfHeight && b.y < mY + harryHalfHeight
     && b.z > mZ && b.z < mZ + 0.1)
    {
      mLife -= 0.1;
      if (mLife < 0.0)
      {
        GameOver();
        return;
      }
      DrawNewLifebar();
      Collision c;
      c.x = mX; c.y = mY; c.z = mZ - 0.01;
      c.timeLength = 2;
      c.image = &mImageCollisionBlue;
      mCollisions.push_back(c);
      continue; //Bullet is gone
    }

    //Check if bullet hit one of the enemies
    bool isHit = false;
    for (auto j = mEnemies.begin(); j != mEnemies.end(); ++j)
    {
      const double halfWidth  = j->image->width()  / 2.0;
      const double halfHeight = j->image->height() / 2.0;
      if (b.x > j->x - halfWidth  && b.x < j->x + halfWidth
       && b.y > j->y - halfHeight && b.y < j->y + halfHeight
       && b.z > j->z - 0.05 && b.z < j->z + 0.05)
      {
        Collision c;
        c.x = b.x; c.y = b.y; c.z = j->z - 0.01;
        c.timeLength = 2;
        c.image = &mImageCollisionGreen;
        mCollisions.push_back(c);
        isHit = true;
        //Damage the enemy
        --j->nHitpoints;
        if (j->nHitpoints <= 0)
        {
          mEnemies.erase(j);
          ++mScore; //Harry scored!
          UpdateTitle();
        }
        break;
      }
    }
    if (!isHit) survivors.push_back(b);
  }
  mBullets.swap(survivors);

  mDrawSoil1 = !mDrawSoil1;
  update();
}

void SpaceHarryGameDialog::GameOver()
{
  mTimerGame.stop();
  mTimerKeyPress.stop();
  mKeys.clear();
  SpaceHarryGameOverDialog * const d = new SpaceHarryGameOverDialog(this);
  d->setAttribute(Qt::WA_DeleteOnClose);
  //Queued, as accepting may delete this dialog, including the game over dialog
  connect(d, &QDialog::finished, this, &QDialog::accept, Qt::QueuedConnection);
  d->open();
}

void SpaceHarryGameDialog::OnKeyPressTimer()
{
  const int speed = 32;
  const int halfWidth  = mImageHarry.width()  / 2;
  const int halfHeight = mImageHarry.height() / 2;
  if (mKeys.count(Qt::Key_Left))
  {
    mX -= speed;
    if (mX < halfWidth) mX = halfWidth;
  }
  if (mKeys.count(Qt::Key_Right))
  {
    mX += speed;
    if (mX + halfWidth > width()) mX = width() - halfWidth;
  }
  if (mKeys.count(Qt::Key_Up))
  {
    mY -= speed;
    if (mY < halfHeight) mY = halfHeight;
  }
  if (mKeys.count(Qt::Key_Down))
  {
    mY += speed;
    if (mY + halfHeight > height()) mY = height() - halfHeight;
  }
  if (mKeys.count(Qt::Key_Space))
  {
    Bullet b;
    b.x = mX;
    b.y = mY;
    b.z = mZ + 0.0501;
    b.dZ = 0.05;
    b.dX = b.dZ * ((width()  / 2.0) - b.x);
    b.dY = b.dZ * ((height() / 2.0) - b.y);
    b.image = &mImageBulletHarry;
    mBullets.push_back(b);
    mKeys.erase(Qt::Key_Space);
  }
  if (mKeys.count(Qt::Key_F1))
  {
    mIsHarryTransparent = !mIsHarryTransparent;
    mKeys.erase(Qt::Key_F1);
  }
}

void SpaceHarryGameDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    QDialog::keyPressEvent(event); //Closes the game
    return;
  }
  //Auto-repeated presses are kept, so holding space keeps firing
  mKeys.insert(event->key());
}

void SpaceHarryGameDialog::keyReleaseEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat()) return;
  mKeys.erase(event->key());
}

void SpaceHarryGameDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  const int skyHeight = height() / 2;

  //Sky
  painter.fillRect(0, 0, width(), skyHeight, QColor(0, 0, 255));
  //Soil, alternating to suggest movement
  painter.drawImage(0, skyHeight, mDrawSoil1 ? mImageSoil1 : mImageSoil2);

  //Collect all sprites
  std::vector<Sprite> sprites;
  sprites.reserve(1 + mBullets.size() + mEnemies.size() + mCollisions.size());
  sprites.push_back(Sprite{mX, mY, mZ,
    mIsHarryTransparent ? &mImageHarryTransparent : &mImageHarry});
  for (const Bullet& b : mBullets) sprites.push_back(Sprite{b.x, b.y, b.z, b.image});
  for (const Enemy& e : mEnemies) sprites.push_back(Sprite{e.x, e.y, e.z, e.image});
  for (const Collision& c : mCollisions) sprites.push_back(Sprite{c.x, c.y, c.z, c.image});

  //Draw from back to front, scaled by distance
  std::stable_sort(sprites.begin(), sprites.end());
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  for (const Sprite& s : sprites)
  {
    const double halfWidth  = (1.0 - s.z) * (s.image->width()  / 2.0);
    const double halfHeight = (1.0 - s.z) * (s.image->height() / 2.0);
    painter.drawImage(
      QRectF(s.x - halfWidth, s.y - halfHeight, 2.0 * halfWidth, 2.0 * halfHeight),
      *s.image);
  }

  //Lifebar
  painter.drawImage(width() - mImageLifebar.width(), 0, mImageLifebar);
}
