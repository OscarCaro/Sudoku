#ifndef Board_h
#define Board_h

#include <string>
#include "Cell.h"

namespace board {

	const int DIM = 9;	//rows and columns
	typedef cell::tCell tBoard[DIM][DIM];

	void init ( tBoard board );	// Initialize board with empty cells and possible [1...9]

	bool checkPos ( const tBoard board, int row, int col, int n );
	// For a given cell, returns true if 'n' is not on it's row/col/subSquare 
	// Used when deleting a cell and updating the Possibles of the related cells (add the value erased to the 
	// tSet of every related cell if it is not on their related cells)
	// It calls:
	bool checkRow ( const tBoard board, int row, int col, int n );
	bool checkCol ( const tBoard board, int row, int col, int n );
	bool checkSubsquare ( const tBoard board, int row, int col, int n );

	void updatePossibles ( tBoard board, int row, int col, int n, bool erase = true );
	// Given a number 'n', it modifies the related cell's set of possible values
	// bool erase: true - eliminate 'n' from sets || false - add 'n' to sets 
	// It calls:
	void updatePosRow ( tBoard board, int row, int n, bool erase = true );
	void updatePosCol ( tBoard board, int col, int n, bool erase = true );
	void updatePosSubSquare ( tBoard board, int row, int col, int n, bool erase = true );
	// SubSquare: square of dim 3x3. There are 9 in a board

	bool load ( const std::string& filename, tBoard board );
	// Receives an initialized board, updates it with Sudoku info in file, and returns bool = true if succeeded
	void draw ( const tBoard board );	// Displays the board on the screen
	bool place ( tBoard board, int row, int col, int c );
	/* Place c in position (row,col) and update possible values of related cells. Works well (bool = true) if:
			- row & col [1...9]
			- c is a possible value for that cell
			- cell was empty	*/
	bool erase ( tBoard board, int row, int col );
	/* Deletes the number at (row, col), sets cell state to 'empty' and updates possible values of related cells
	   Works well (bool = true) if:
			- row & col [1...9]
			- cell was previously filled	*/
	bool full ( const tBoard board );		// Bool = true if board is full
	void possible ( const tBoard board, int row, int col );
	// Displays possible values of the cell at (row, col) (row and col [1..9])
	void fillSimple ( tBoard board );
	// Solves all one-possibility cells and updates possible values of related cells

}

#endif