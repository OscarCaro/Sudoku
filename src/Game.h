#ifndef Game_h
#define Game_h

#include <string>
#include "Board.h"

namespace game {

	typedef struct {
		int score;
		std::string filename;
	}tSudoku;

	typedef struct {
		board::tBoard board;
		bool boardFull;
	}tGame;

	void initGame ( tGame& game, const tSudoku& sudoku );
	// Initializes Game: new board initialized, non-finished game
	void displayGame ( const tGame& game, const tSudoku& sudoku );	// Displays Sudoku info and board
	bool loadGame ( tGame& game, const tSudoku& sudoku );
	// Updates the game board with the content of the file corresponding to the filename of sudoku.
	void askCellPos ( int& row, int& col );
	// Returns row and col chosen by user (values from 0 to 8)
	int askNum ();
	// Returns number chosen by user (value from 1 to 9)
	int menuPlay ();		// Displays PlayMenu and returns choice
	int playSudoku ( const tSudoku& sudoku );
	// Initialize a new game, performs all tasks related to play that game
	// Returns: sudoku’s associated score if sudoku is completed | 0 otherwise

}

#endif 
