#ifndef _IO_
#define _IO_
//------------------------------------------------------------------------------
#include <SDL/include/SDL.h>
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"
#pragma comment (lib, "SDL/lib/SDL1.lib")
#pragma comment (lib, "SDL/lib/SDL2-bcb.lib")
#pragma comment (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static-bcb.lib")





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

};

#endif
