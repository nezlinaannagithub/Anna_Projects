#include "stdafx.h"
#include "Board.h"
#include "IO.h"


Board::Board (Shapes *sShapes, int sScreenHeight)
{

	// Get the screen height
	mScreenHeight = sScreenHeight;

	// Get the pointer to the pieces class
	mShapes = sShapes;

	//Init the board blocks with free positions
	InitBoard();
}
void Board::InitBoard()
{
	/*for (int i=0; i < 10; i++)
		for (int j = 0; i < 20; j++)
			if (mBoard[i][j]==0) mBoard[i][j] = 0;*/
			
		
}
void Board::StorePiece (int sX, int sY, int sShape, int sRott)
{

	for (int i1 = sX, i2 = 0; i1 < sX + PIECE_BLOCKS; i1++, i2++)
	{
        for (int j1 = sY, j2 = 0; j1 < sY + PIECE_BLOCKS; j1++, j2++)
		{
			if (mShapes->GetBlockType(sShape, sRott, j2, i2) != 0)
			{
				mBoard[i1][j1] = 1;

			}
        }
    }
}
bool Board::IsGameOver()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (mBoard[i][0] == 1) return true;
    }
    return false;
}
void Board::DeleteLine (int sY)
{
	for (int j = sY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
	int count = + 10;
}
void Board::DeletePossibleLines ()
{
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int i = 0;
        while (i < BOARD_WIDTH)
        {
			if (mBoard[i][j] != 1) break;
            i++;
        }
        if (i == BOARD_WIDTH) DeleteLine (j);
    }
}
bool Board::IsBlockFree (int sX, int sY)
{
    if (mBoard [sX][sY] == 0) return true; else return false;
}
int Board::GetXInPixels (int sPos)
{
	return  ( ( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (sPos * BLOCK_SIZE) );
}
int Board::GetYInPixels (int sPos)
{
	return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (sPos * BLOCK_SIZE) );
}

bool Board::IsMovementPossible (int sX, int sY, int sShape, int sRott)
{
	for (int i1 = sX, i2 = 0; i1 < sX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = sY, j2 = 0; j1 < sY + PIECE_BLOCKS; j1++, j2++)
		{
			if (    i1 < 0           ||
				i1 > BOARD_WIDTH  - 1    ||
				j1 > BOARD_HEIGHT - 1)
			{
				if (mShapes->GetBlockType (sShape, sRott, j2, i2) != 0)
					return 0;
			}
			if (j1 >= 0)
			{
				if ((mShapes->GetBlockType (sShape, sRott, j2, i2) != 0) &&
					(!IsBlockFree (i1, j1)) )
                    return false;
            }
		}
	}
	return true;
}
