#ifndef SudokuList_h
#define SudokuList_h

#include <string>
#include "Game.h"

namespace sudokuList {

	const int MAX_SUDOKUS = 20;
	const std::string sudokuListFile = "sudokuList.txt";

	typedef game::tSudoku tSudokuArray[MAX_SUDOKUS];

	typedef struct {
		tSudokuArray sudokuArray;
		int counter;
	}tSudokuList;		// List of up to 20 sudokus

	void createList ( tSudokuList& list );		// Initializes list as an empty list.
	bool load ( tSudokuList& list ); // Loads the content of the file "sudokulist.txt" in list. True if succeeded
	void display ( const tSudokuList& list );	// Displays the list of sudokus
	game::tSudoku sudokuListMenu ( const tSudokuList& list );	//Return the chosen sudoku to play
	bool save ( const tSudokuList& list );	// Stores the content of list in sudokulist.txt
	bool registerSudoku ( tSudokuList& list );
	/* Asks for a new sudoku’s data and inserts the sudoku in the appropriate position (ordered).
	   Ok if no other sudoku with that filename exists in list, and list is not full */
	void insert ( tSudokuList& list, const game::tSudoku& sudoku, int pos );
	// Inserts the sudoku in list at position pos 
	bool findFile ( const tSudokuList& list, const std::string& filename );
	// Returns a boolean indicating whether a sudoku with the filename already exists.
	int findPosition ( const tSudokuList& list, const game::tSudoku& sudoku );
	// Returns the position in list where a new sudoku should be inserted. 
	// Order is: by score (ascending), and if two scores are the same, by filename (ascending)
	int binarySearchPosition ( const tSudokuArray& list, const game::tSudoku& sudoku, int beg, int end );

}

#endif