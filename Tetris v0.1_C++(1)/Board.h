#ifndef _BOARD_
#define _BOARD_
//-----------------------------------------------------------------------------
#include "Shapes.h"
//-----------------------------------------------------------------------------
#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 20
#define BOARD_POSITION 320
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5
//-----------------------------------------------------------------------------
//                           ????? ???????? ????
//-----------------------------------------------------------------------------
class Board
{
public:

  Board (Shapes *sShapes, int sScreenHeight);

	int GetXInPixels         (int sPos);
	int GetYInPixels         (int sPos);
	bool IsBlockFree            (int sX, int sY);
	bool IsMovementPossible     (int sX, int sY, int sPiece, int sRotation);
	void StorePiece             (int sX, int sY, int sPiece, int sRotation);
    void DeletePossibleLines    ();
	bool IsGameOver             ();

private:
	enum { CELL_EMPTY, CELL_FILLED };
	int mBoard [BOARD_WIDTH][BOARD_HEIGHT];
	Shapes *mShapes;
	int mScreenHeight;

	void InitBoard();
    void DeleteLine(int sY);
};

#endif
