#include "Game.h"

int main()
{
	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();
	
	Pieces mPieces;
	
	Board mBoard(&mPieces, mScreenHeight);
	
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);
	
	unsigned long mTime1 = SDL_GetTicks();
	
	while(!mIO.IsKeyDown(SDLK_ESCAPE))
	{
		mIO.ClearScreen();
		mGame.DrawScreen();
		if(mGame.CheckPauseFlag())
			mIO.DrawPause();
		
		mIO.UpdateScreen();
		
		int mKey = mIO.Pollkey();
		
		switch(mKey)
		{
			case (SDLK_SPACE):
				mGame.ReversePauseFlag();
				break;
			
			case (SDLK_RIGHT):
				if(mGame.CheckPauseFlag())
					break;
			
				if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX++;				
				break;
				
			case (SDLK_LEFT):
				if(mGame.CheckPauseFlag())
					break;			
			
				if (mBoard.IsPossibleMovement (mGame.mPosX -1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;				
				break;

			case (SDLK_DOWN):
				if(mGame.CheckPauseFlag())
					break;			
			
				if (mBoard.IsPossibleMovement (mGame.mPosX , mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;				
				break;

			case (SDLK_x):
				if(mGame.CheckPauseFlag())
					break;			
			
				// Check collision from up to down
				while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }
			 
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);
			 
				mBoard.DeletePossibleLines ();
			 
				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}
			 
				mGame.CreateNewPiece(); 
			break;
			
			case (SDLK_z):
				if(mGame.CheckPauseFlag())
					break;			
			
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
							mGame.mRotation = (mGame.mRotation + 1) % 4;
			break;				
		}
		
		if(mGame.CheckPauseFlag())
		{
			continue;
		}
		
		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

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
}