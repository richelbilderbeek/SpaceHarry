//---------------------------------------------------------------------------
/*
  Space Harry, a simple 'Space Harrier' clone
<<<<<<< HEAD
  Copyright (C) 2007  Rich�l Bilderbeek
=======
  Copyright (C) 2007  Richel Bilderbeek
>>>>>>> develop

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
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSpaceHarryGameOver.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSpaceHarryGameOver *FormSpaceHarryGameOver;
//---------------------------------------------------------------------------
__fastcall TFormSpaceHarryGameOver::TFormSpaceHarryGameOver(TComponent* Owner)
        : TForm(Owner), mCanClose(false)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryGameOver::Timer1Timer(TObject *Sender)
{
  mCanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryGameOver::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (mCanClose == true) Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSpaceHarryGameOver::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (mCanClose == true) Close();
}
//---------------------------------------------------------------------------
