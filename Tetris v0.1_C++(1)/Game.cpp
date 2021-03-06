 // ------ Includes -----
#ifndef LINUX
#include <windows.h>
#endif
#include "Game.h"


/*
======================================
Init
======================================
*/
Game::Game(Board *sBoard, Shapes *sShapes, IO *sIO, int sScreenHeight)
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

	mNextShape      = GetRand (0, 6);
	mNextRott   = 0;
    mNextPosX       = BOARD_WIDTH + 5;
    mNextPosY       = 5;
}
void Game::CreateNewPiece()
{
	mShape         = mNextShape;
	mRott       = mNextRott;
	mPosX           = (BOARD_WIDTH / 2) + mShapes->GetXInitPos (mShape, mRott);
	mPosY           = mShapes->GetYInitPos (mShape, mRott);

	mNextShape      = GetRand (0, 6);
	mNextRott   = 0;
}
void Game::DrawPiece (int sX, int sY, int sShape, int sRott)
{
	color mColor;

	int mPixelsX = mBoard->GetXInPixels (sX);
	int mPixelsY = mBoard->GetYInPixels (sY);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{

			switch (mShapes->GetBlockType (sShape, sRott, j, i))
			{
				case 1: mColor = GREEN; break;
				case 2: mColor = BLUE; break;
			}

			if (mShapes->GetBlockType (sShape, sRott, j, i) != 0)
				mIO->DrawRectangle   (mPixelsX + i * BLOCK_SIZE,
									mPixelsY + j * BLOCK_SIZE,
									(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
									(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
									mColor);
		}
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
                mIO->DrawRectangle ( mX1 + i * BLOCK_SIZE,
                                        mY + j * BLOCK_SIZE,
                                        (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                        (mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                        RED);
        }
    }
}
void Game::DrawScene ()
{
	DrawBoard ();
	DrawPiece (mPosX, mPosY, mShape, mRott);
    DrawPiece (mNextPosX, mNextPosY, mNextShape, mNextRott);
}
