#include "Game.h"

/* 
======================================									
Init
====================================== 
*/
Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;
	mPauseFlag = false;

	// Game initialization
	InitGame ();
}

/* 
======================================                                  
Get a random int between to integers
 
Parameters:
>> pA: First number
>> pB: Second number
====================================== 
*/
int Game::GetRand(int pA, int pB)
{
	return rand() % (pB -pA + 1)+pA;
}

/* 
======================================                                  
Initial parameters of the game
====================================== 
*/
void Game::InitGame()
{
	srand((unsigned int) time(NULL));
	
	mPiece			= GetRand(0, 6);
	mRotation		= GetRand(0, 3);
	mPosX			= (BOARD_WIDTH / 2) + mPieces -> GetXInitialPosition(mPiece, mRotation);
	mPosY			= mPieces -> GetYInitialPosition(mPiece, mRotation);
	
	mNextPiece	= GetRand(0, 6);
	mNextRotation	= GetRand(0, 3);
	mNextPosX	= BOARD_WIDTH + 5;
	mNextPosY	= 5;
}

/* 
======================================                                  
Create a random piece
====================================== 
*/
void Game::CreateNewPiece()
{
    // The new piece
    mPiece          = mNextPiece;
    mRotation       = mNextRotation;
    mPosX           = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY           = mPieces->GetYInitialPosition (mPiece, mRotation);
 
    // Random next piece
    mNextPiece      = GetRand (0, 6);
    mNextRotation   = GetRand (0, 3);	
}

/* 
======================================                                  
Draw piece
 
Parameters:
 
>> pX:        Horizontal position in blocks
>> pY:        Vertical position in blocks
>> pPiece:    Piece to draw
>> pRotation: 1 of the 4 possible rotations
====================================== 
*/
void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
	color mColor;
	
	int mPixelsX = mBoard -> GetXPosInPixels(pX);
	int mPixelsY = mBoard -> GetYPosInPixels(pY);
	
	for(int i = 0; i < PIECE_BLOCKS; ++i)
	{
		for(int j = 0; j < PIECE_BLOCKS; ++j)
		{
			switch(mPieces -> GetBlockType(pPiece, pRotation, j, i))
			{
				case 1: mColor = GREEN;	break;
				case 2: mColor = BLUE;		break;
			}
			
			if(mPieces -> GetBlockType(pPiece, pRotation, j, i) != 0)
				mIO -> DrawRectangle(mPixelsX + i * BLOCK_SIZE,
														mPixelsY + j*BLOCK_SIZE, 
														mPixelsX + i*BLOCK_SIZE + BLOCK_SIZE - 1,
														mPixelsY + j*BLOCK_SIZE + BLOCK_SIZE - 1,
														mColor);
		}
	}
}

/* 
======================================                                  
Draw board
 
Draw the two lines that delimit the board
====================================== 
*/
void Game::DrawBoard()
{
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * BOARD_WIDTH / 2) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * BOARD_WIDTH / 2) ;
	int mY = mScreenHeight - BLOCK_SIZE * BOARD_HEIGHT;
	
	mIO -> DrawRectangle( mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
	mIO -> DrawRectangle( mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);
	
	mX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {   
            // Check if the block is filled, if so, draw it
            if (!mBoard->IsFreeBlock(i, j))  
                mIO->DrawRectangle ( mX1 + i * BLOCK_SIZE, 
                                        mY + j * BLOCK_SIZE, 
                                        (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1, 
                                        (mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, 
                                        RED);
        }
    } 	
}

/* 
======================================                                  
Draw scene
 
Draw all the objects of the scene
====================================== 
*/
void Game::DrawScreen ()
{
    DrawBoard ();
    DrawPiece (mPosX, mPosY, mPiece, mRotation);
    DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}

/* 
======================================                                  
Reverse pause flag
 
====================================== 
*/
void Game::ReversePauseFlag()
{
	mPauseFlag = !mPauseFlag;
}

/* 
======================================                                  
Check pause flag

====================================== 
*/
bool Game::CheckPauseFlag()
{
	return mPauseFlag;
}