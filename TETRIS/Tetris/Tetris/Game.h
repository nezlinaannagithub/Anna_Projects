#ifndef _GAME_
#define _GAME_
//------------------------------------------------------------------------------
#include "Shapes.h"
#include "Board.h"
#include <time.h>
#include "IO.h"
#include <SDL.h>
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")
#undef main
//------------------------------------------------------------------------------
#define WAIT_TIME 700
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Game
{
public:

	Game (Board *sBoard, Shapes *sShapes, IO *sIO, int sdScreenHeight);

    void DrawScene ();
	void StoreColor(int sX, int sY, int sShape, int sRott);
	void DeleteColor(int sY);
	void DeletePossibleColors();
    void CreateNewPiece ();


	int mPosX, mPosY;
	int mShape, mRott;

private:

	int mColorBoard[10][20];

	int mScreenHeight;
	int mNextPosX, mNextPosY;
	int mNextShape, mNextRott;

	IO *mIO;
	Board *mBoard;
	Shapes *mShapes;
	

	int GetRand (int sA, int sB);
	void InitGame();
	void DrawPiece (int sX, int sY, int sPiece, int sRott);
	void DrawNextPiece(int sX, int sY, int sShape, int sRott);
	void DrawBoard ();
};

#endif
