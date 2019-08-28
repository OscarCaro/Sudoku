#include "checkML.h"
#include "Game.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
using namespace game;

void game::initGame ( tGame& game, const tSudoku& sudoku ) {
	game.boardFull = false;
	board::init ( game.board );
}

void game::displayGame ( const tGame& game, const tSudoku& sudoku ) {
	cout << endl << "Playing: " << sudoku.filename.substr ( 0, sudoku.filename.size () - 4 );	// avoid the .txt
	cout << ". Score: " << sudoku.score << " pts." << endl << endl;
	board::draw ( game.board );
}

bool game::loadGame ( tGame & game, const tSudoku & sudoku ) {
	return board::load ( sudoku.filename, game.board );
}

void game::askCellPos ( int& row, int& col ) {
	do {
		cout << "Row (1 - 9): ";
		cin >> row;
	} while ( row < 1 || row > 9 );
	do {
		cout << "Column (1 - 9): ";
		cin >> col;
	} while ( row < 1 || row > 9 );
	// Matrix range: from 0 to 8. So:
	row--;
	col--;
}

int game::askNum () {
	int num;
	do {
		cout << "Number (1 - 9): ";
		cin >> num;
	} while ( num < 1 || num > 9 );
	return num;
}

int game::menuPlay () {
	int choice;

	do {
		cout << "Play Menu:   " << "1. Possible values for a cell" << endl;;
		cout << setw ( 13 ) << "" << "2. Put a value in a cell" << endl;
		cout << setw ( 13 ) << "" << "3. Delete cell value" << endl;
		cout << setw ( 13 ) << "" << "4. Restart the board" << endl;
		cout << setw ( 13 ) << "" << "5. Autofill simple cells" << endl;
		cout << setw ( 13 ) << "" << "0. Go back to main menu" << endl;
		cout << "Choice: ";
		cin >> choice;
	} while ( choice < 0 || choice > 5 );

	return choice;
}

int game::playSudoku ( const tSudoku & sudoku ) {
	tGame game;
	initGame ( game, sudoku );
	loadGame ( game, sudoku );

	int choice, row, col, num, returnValue;
	char aux;

	do {
		displayGame ( game, sudoku );
		choice = menuPlay ();
		switch ( choice ) {
			case 1:
				askCellPos ( row, col );
				if ( game.board[row][col].state == cell::fixed ) {
					cout << "Fixed Cell -> No possible values" << endl;
				}
				else {
					set::display ( game.board[row][col].possible );
				}
				break;

			case 2:
				askCellPos ( row, col );
				num = askNum ();
				if ( !board::place ( game.board, row, col, num ) ) {
					cout << "Error: Non-empty cell or 'number' shouldn't be placed there" << endl;
				}
				break;

			case 3:
				askCellPos ( row, col );
				board::erase ( game.board, row, col );
				break;

			case 4:
				// Warning message
				cout << "Are you sure you want to restart the game? (y/n): ";
				cin >> aux;
				if ( toupper ( aux ) == 'Y' ) {
					initGame ( game, sudoku );
					loadGame ( game, sudoku );
				}
				break;

			case 5:
				board::fillSimple ( game.board );
				break;

			case 0:
				// Warning message
				cout << "Are you sure you want to exit the game? (y/n): ";
				cin >> aux;
				break;
		}
	} while ( !board::full ( game.board ) && !(choice == 0 && toupper ( aux ) == 'Y') );

	if ( board::full ( game.board ) ) {
		returnValue = sudoku.score;
		displayGame ( game, sudoku );
	}
	else {
		returnValue = 0;
	}

	return (returnValue);
}