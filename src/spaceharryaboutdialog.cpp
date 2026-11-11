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
#include "spaceharryaboutdialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QVBoxLayout>

#include "spaceharrymenudialog.h" //For CreateCourierFont

namespace {
  QLabel * CreateLabel(const QString& text, const QFont& font, const int height, QWidget * parent)
  {
    QLabel * const label = new QLabel(text, parent);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    label->setFixedHeight(height);
    return label;
  }
}

SpaceHarryAboutDialog::SpaceHarryAboutDialog(QWidget *parent)
  : QDialog(parent)
{
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  setWindowTitle("Space Harry (C) 2007 Richel Bilderbeek");
  setFixedSize(758, 585);
#ifdef Q_OS_WASM
  //The web page is the window: no title bar
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif

  const QFont bigFont = CreateCourierFont(64, true, true);
  const QFont smallFont = CreateCourierFont(16, false);
  QFont linkFont = CreateCourierFont(16, true);

  QLabel * const image = new QLabel(this);
  image->setPixmap(QPixmap(":/about.png"));

  QVBoxLayout * const textLayout = new QVBoxLayout;
  textLayout->setSpacing(0);
  textLayout->addWidget(CreateLabel("Space", bigFont, 74, this));
  textLayout->addWidget(CreateLabel("Harry", bigFont, 74, this));
  textLayout->addWidget(CreateLabel("(C) 2007 Richel Bilderbeek", smallFont, 36, this));
  textLayout->addWidget(CreateLabel("Programmed from the 27th", smallFont, 36, this));
  textLayout->addWidget(CreateLabel("November 2007 to and", smallFont, 36, this));
  textLayout->addWidget(CreateLabel("including the 3rd of", smallFont, 36, this));
  textLayout->addWidget(CreateLabel("December 2007.", smallFont, 36, this));
  textLayout->addWidget(CreateLabel("Licenced under GPL 3.0", smallFont, 36, this));
  textLayout->addWidget(CreateLabel("http://www.richelbilderbeek.nl", linkFont, 36, this));
  textLayout->addStretch();

  QHBoxLayout * const topLayout = new QHBoxLayout;
  topLayout->setSpacing(0);
  topLayout->addWidget(image);
  topLayout->addLayout(textLayout, 1);

  QPlainTextEdit * const licence = new QPlainTextEdit(this);
  licence->setReadOnly(true);
  licence->setFont(CreateCourierFont(11, false));
  licence->setPlainText(
    "  Space Harry, a simple 'Space Harrier' clone\n"
    "  Copyright (C) 2007  Richel Bilderbeek\n"
    "\n"
    "  This program is free software: you can redistribute it and/or modify\n"
    "  it under the terms of the GNU General Public License as published by\n"
    "  the Free Software Foundation, either version 3 of the License, or\n"
    "  (at your option) any later version.\n"
    "\n"
    "  This program is distributed in the hope that it will be useful,\n"
    "  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "  GNU General Public License for more details.\n"
    "\n"
    "  You should have received a copy of the GNU General Public License\n"
    "  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n");

  QVBoxLayout * const layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addLayout(topLayout);
  layout->addWidget(licence, 1);
}
