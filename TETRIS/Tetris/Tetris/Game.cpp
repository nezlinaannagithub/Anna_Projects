 // ------ Includes -----
#include "stdafx.h"
#include <windows.h>
#include "Game.h"


/*
======================================
Init
======================================
*/
color mColor;
color mNextColor;
color mArrayColor[10][20];
Game::Game(Board *sBoard, Shapes *sShapes, IO *sIO,  int sScreenHeight)
{
	mScreenHeight = sScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = sBoard;
	mShapes = sShapes;
	mIO = sIO;

	// Game initialization
	InitGame ();
}
int Game::GetRand (int sA, int sB)
{
    return rand () % (sB - sA + 1) + sA;
}
void Game::InitGame()
{
    srand ((unsigned int) time(NULL));

	mShape          = GetRand (0, 6);
	mRott       = 0;
	mPosX           = (BOARD_WIDTH / 2) + mShapes->GetXInitPos (mShape, mRott);
	mPosY           = mShapes->GetYInitPos (mShape, mRott);	
	switch (GetRand(0, 5))
	{
	case 0: mColor = RED; break;
	case 1:mColor =GREEN ;break;
	case 2:mColor =YELLOW ;break;
	case 3:mColor =BLUE ;break;
	case 4:mColor =MAGENTA ;break;
	case 5:mColor =CYAN ;break;
	}	

	mNextShape      = GetRand (0, 6);
	mNextRott   = 0;
    mNextPosX       = BOARD_WIDTH + 2;
    mNextPosY       = 1;
	switch (GetRand(0, 5))
	{
	case 0: mNextColor = RED;break;
	case 1:mNextColor = GREEN;break;
	case 2:mNextColor = YELLOW;break;
	case 3:mNextColor = BLUE;break;
	case 4:mNextColor = MAGENTA;break;
	case 5:mNextColor = CYAN;break;
	}

}
void Game::CreateNewPiece()
{

	mShape         = mNextShape;
	mRott       = mNextRott;
	mPosX           = (BOARD_WIDTH / 2) + mShapes->GetXInitPos (mShape, mRott);
	mPosY           = mShapes->GetYInitPos (mShape, mRott);

	mColor = mNextColor;

	mNextShape      = GetRand (0, 6);
	mNextRott   = 0;
	switch (GetRand(0, 5))
	{
	case 0: mNextColor = RED;break;
	case 1:mNextColor = GREEN;break;
	case 2:mNextColor = YELLOW;break;
	case 3:mNextColor = BLUE;break;
	case 4:mNextColor = MAGENTA;break;
	case 5:mNextColor = CYAN;break;
	}
}
void Game::DrawPiece (int sX, int sY, int sShape, int sRott)
{
	//color mColor;

	int mPixelsX = mBoard->GetXInPixels (sX);
	int mPixelsY = mBoard->GetYInPixels (sY);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			

			if (mShapes->GetBlockType (sShape, sRott, j, i) != 0)
				mIO->DrawRectangle   (mPixelsX + i * BLOCK_SIZE,
									mPixelsY + j * BLOCK_SIZE,
									(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
									(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, mColor);
									 
		}
	}
}
void Game::DrawNextPiece(int sX, int sY, int sShape, int sRott)
{
	//color mColor;

	int mPixelsX = mBoard->GetXInPixels(sX);
	int mPixelsY = mBoard->GetYInPixels(sY);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{

			if (mShapes->GetBlockType(sShape, sRott, j, i) != 0)
				mIO->DrawRectangle(mPixelsX + i * BLOCK_SIZE,
					mPixelsY + j * BLOCK_SIZE,
					(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, mNextColor);

		}
	}
}
void Game::StoreColor(int sX, int sY, int sShape, int sRott)
{
	for (int i1 = sX, i2 = 0; i1 < sX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = sY, j2 = 0; j1 < sY + PIECE_BLOCKS; j1++, j2++)
		{
			if (mShapes->GetBlockType(sShape, sRott, j2, i2) != 0)
			{


				switch (mColor)
				{
				case RED: mColorBoard[i1][j1] = 0; break;
				case GREEN: mColorBoard[i1][j1] = 1;break;
				case YELLOW: mColorBoard[i1][j1] = 2;break;
				case BLUE: mColorBoard[i1][j1] = 3;break;
				case MAGENTA: mColorBoard[i1][j1] = 4;break;
				case CYAN: mColorBoard[i1][j1] = 5;break;
				}

			}
		}
	}
}
void Game::DeleteColor(int sY)
{
	for (int j = sY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mColorBoard[i][j] = mColorBoard[i][j - 1];
		}
	}
}
void Game::DeletePossibleColors()
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mColorBoard[i][j] <5) break;
			i++;
		}
		if (i == BOARD_WIDTH) DeleteColor(j);
	}
}
void Game::DrawBoard ()
{
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);

    mIO->DrawRectangle (mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

    mX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			if (!mBoard->IsBlockFree(i, j))
			{
				switch (mColorBoard[i][j])
				{
				case 0: { mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED); break;}
				case 1: { mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, GREEN); break;}
				case 2: { mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, YELLOW); break;}
				case 3: { mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, BLUE); break; }
				case 4: { mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, MAGENTA); break; }
				case 5: { mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, CYAN); break; }
				}
				
				/*mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED); */
					
			}
        }
    }

}
void Game::DrawScene ()
{


	DrawBoard ();
	DrawPiece (mPosX, mPosY, mShape, mRott);
    DrawNextPiece (mNextPosX, mNextPosY, mNextShape, mNextRott);

}
