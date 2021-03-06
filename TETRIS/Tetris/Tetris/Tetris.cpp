// Tetris.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
#include <SDL.h>

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

int main(int argc, char **argv)
{
	HideConsole();
_Start:

	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();
    mIO.Getkey();
	// Pieces
	Shapes mShapes;

	// Board
	Board mBoard(&mShapes, mScreenHeight);

	// Game
	Game mGame(&mBoard, &mShapes, &mIO, mScreenHeight);

	
	// Get the actual clock milliseconds (SDL)
	unsigned long mTime1 = SDL_GetTicks();

	// ----- Main Loop -----
	while (!mIO.IsKeyDown(SDLK_ESCAPE))
	{
	
		   
			// ----- Draw -----

			mIO.ClearScreen(); 		// Clear screen
			mGame.DrawScene();			// Draw staff
			mIO.UpdateScreen();		// Put the graphic context in the screen

									// ----- Input -----

			int mKey = mIO.Pollkey();

			switch (mKey)
			{
			case (SDLK_RIGHT):
			{
				if (mBoard.IsMovementPossible(mGame.mPosX + 1, mGame.mPosY, mGame.mShape, mGame.mRott))
					mGame.mPosX++;
				break;
			}

			case (SDLK_LEFT):
			{
				if (mBoard.IsMovementPossible(mGame.mPosX - 1, mGame.mPosY, mGame.mShape, mGame.mRott))
					mGame.mPosX--;
				break;
			}

			case (SDLK_DOWN):
			{
				if (mBoard.IsMovementPossible(mGame.mPosX, mGame.mPosY + 1, mGame.mShape, mGame.mRott))
					mGame.mPosY++;
				break;
			}

			case (SDLK_x):
			{
				// Check collision from up to down
				while (mBoard.IsMovementPossible(mGame.mPosX, mGame.mPosY, mGame.mShape, mGame.mRott)) { mGame.mPosY++; }

				mGame.StoreColor(mGame.mPosX, mGame.mPosY - 1, mGame.mShape, mGame.mRott);

				mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mShape, mGame.mRott);

				mBoard.DeletePossibleLines();
				mGame.DeletePossibleColors();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					//exit(0);
				}

				mGame.CreateNewPiece();

				break;
			}

			case (SDLK_z):
			{
				if (mBoard.IsMovementPossible(mGame.mPosX, mGame.mPosY, mGame.mShape, (mGame.mRott + 1) % 4))
					mGame.mRott = (mGame.mRott + 1) % 4;

				break;
			}
			case (SDLK_r):
			{
				goto _Start;
			}
			case (SDLK_g):
			{
				while (!mIO.Getkey())
				{
					SDL_Delay(1);
				}
			}
			}

			// ----- Vertical movement -----

			unsigned long mTime2 = SDL_GetTicks();

			if ((mTime2 - mTime1) > WAIT_TIME)
			{
				if (mBoard.IsMovementPossible(mGame.mPosX, mGame.mPosY + 1, mGame.mShape, mGame.mRott))
				{
					mGame.mPosY++;
				}
				else
				{
					mGame.StoreColor(mGame.mPosX, mGame.mPosY, mGame.mShape, mGame.mRott);

					mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mShape, mGame.mRott);

					mBoard.DeletePossibleLines();
					mGame.DeletePossibleColors();

					if (mBoard.IsGameOver())
					{
						//mIO.Getkey();
						goto _Start;
						//exit(0);
					}

					mGame.CreateNewPiece();
				}

				mTime1 = SDL_GetTicks();
			}
			
	}
	
 
   return 0;
}

