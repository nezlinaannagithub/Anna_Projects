//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Shapes.h"
#include "Board.h"
#include "Game.h"
#include "IO.h"
#include "Main.cpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
Shapes *Sh;
IO *mIO;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
   {
   mIO->InitGraph();


}


//---------------------------------------------------------------------------




