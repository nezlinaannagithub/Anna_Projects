#ifndef _GAME_
#define _GAME_
//------------------------------------------------------------------------------
#include "Shapes.h"
#include "Board.h"
#include "IO.h"
#include <time.h>
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
    void CreateNewPiece ();

	int mPosX, mPosY;
	int mShape, mRott;

private:

	int mScreenHeight;
	int mNextPosX, mNextPosY;
	int mNextShape, mNextRott;

	Board *mBoard;
	Shapes *mShapes;
	IO *mIO;

	int GetRand (int sA, int sB);
	void InitGame();
	void DrawPiece (int sX, int sY, int sPiece, int sRott);
	void DrawBoard ();
};

#endif
