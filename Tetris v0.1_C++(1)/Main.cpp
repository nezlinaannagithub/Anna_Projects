#ifndef MAIN
#define MAIN
#include "Game.h"

#include <windows.h>

/*
==================
Main
==================
*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();

	// Pieces
	Shapes mShapes;

	// Board
	Board mBoard (&mShapes, mScreenHeight);

	// Game
	Game mGame (&mBoard, &mShapes, &mIO, mScreenHeight);

	// Get the actual clock milliseconds (SDL)
	unsigned long mTime1 = SDL_GetTicks();

	// ----- Main Loop -----

	while (!mIO.IsKeyDown (SDLK_ESCAPE))
	{
		// ----- Draw -----

		mIO.ClearScreen (); 		// Clear screen
		mGame.DrawScene ();			// Draw staff
		mIO.UpdateScreen ();		// Put the graphic context in the screen

		// ----- Input -----

		int mKey = mIO.Pollkey();

		switch (mKey)
		{
			case (SDLK_RIGHT):
			{
				if (mBoard.IsMovementPossible (mGame.mPosX + 1, mGame.mPosY, mGame.mShape, mGame.mRott))
					mGame.mPosX++;
					break;
			}

			case (SDLK_LEFT):
			{
				if (mBoard.IsMovementPossible (mGame.mPosX - 1, mGame.mPosY, mGame.mShape, mGame.mRott))
					mGame.mPosX--;
				break;
			}

			case (SDLK_DOWN):
			{
				if (mBoard.IsMovementPossible (mGame.mPosX, mGame.mPosY + 1, mGame.mShape, mGame.mRott))
					mGame.mPosY++;
				break;
			}

			case (SDLK_x):
			{
				// Check collision from up to down
				while (mBoard.IsMovementPossible(mGame.mPosX, mGame.mPosY, mGame.mShape, mGame.mRott)) { mGame.mPosY++; }

				mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mShape, mGame.mRott);

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();

				break;
			}

			case (SDLK_z):
			{
				if (mBoard.IsMovementPossible (mGame.mPosX, mGame.mPosY, mGame.mShape, (mGame.mRott + 1) % 4))
					mGame.mRott = (mGame.mRott + 1) % 4;

				break;
			}
		}

		// ----- Vertical movement -----

		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			if (mBoard.IsMovementPossible (mGame.mPosX, mGame.mPosY + 1, mGame.mShape, mGame.mRott))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mShape, mGame.mRott);

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}
     return 0;
}
#endif