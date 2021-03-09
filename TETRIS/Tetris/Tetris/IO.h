#ifndef _IO_
#define _IO_
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX};
// -----------------------------------------------------------------------------
//                                   IO
// -----------------------------------------------------------------------------

class IO
{
public:

    IO                      ();

	void DrawRectangle      (int sX1, int sY1, int sX2, int sY2, enum color sC);
    void ClearScreen        ();
    int GetScreenHeight     ();
    int InitGraph           ();
    int Pollkey             ();
    int Getkey              ();
    int IsKeyDown           (int pKey);
    void UpdateScreen       ();
	void WriteText(int sX1, int sY1, int sX2, int sY2, enum color sC);

};

#endif
