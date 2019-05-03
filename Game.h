#ifndef _GAME_H
#define _GAME_H

#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>

#define WAIT_TIME 700

// --------------------------------------------------------------------------------
//                                   Game
// --------------------------------------------------------------------------------

class Game
{
public:
	
		Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);
		
		void DrawScreen();
		void CreateNewPiece();
		void ReversePauseFlag();
		bool CheckPauseFlag();
		
		int mPosX, mPosY;
		int mPiece, mRotation;
		
private:

	int 		mScreenHeight;
	int 		mNextPosX, mNextPosY;
	int 		mNextPiece, mNextRotation;
	bool	mPauseFlag;
	
	Board *mBoard;
	Pieces *mPieces;
	IO *mIO;
	
	int 		GetRand(int pA, int pB);
	void	InitGame();
	void	DrawPiece(int pX, int pY, int pPiece, int pRotation);
	void	DrawBoard();
};

#endif