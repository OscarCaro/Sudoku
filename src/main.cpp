// Author: Óscar Caro Navarro  (alone)

#include "checkML.h"
#include "SudokuList.h"
#include "PlayerList.h"
#include <iostream>
#include <iomanip>

using namespace std;

int menu ();

int main () {

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	sudokuList::tSudokuList sudokuList;
	playerList::tPlayerList playerList;
	int choice, score;

	sudokuList::createList ( sudokuList );
	playerList::create ( playerList );

	if ( !sudokuList::load ( sudokuList ) ) {
		cout << sudokuList::sudokuListFile << " not available" << endl;
		system ( "pause" );
	}
	else if ( !playerList::load ( playerList ) ) {
		cout << playerList::fileName << " not available" << endl;
		system ( "pause" );
	}
	else {
		playerList::sortById ( playerList, 0, playerList.count - 1 );	// Sorted in decreasing order, so:
		playerList::reverseOrder ( playerList, 0, playerList.count - 1 );
		do {
			choice = menu ();
			switch ( choice ) {
				case 1:
				{
					game::tSudoku sudoku = sudokuList::sudokuListMenu ( sudokuList );
					score = game::playSudoku ( sudoku );
					if ( score != 0 ) {
						cout << "=================================================" << endl;
						cout << "Congratulations. You win " << score << " point(s)" << endl;
						cout << "Stored Players: " << endl;
						playerList::display ( playerList );
						playerList::playerScore ( playerList, score );
						cout << "=================================================" << endl;
					}
					break;
				}

				case 2:
					cout << endl;
					playerList::display ( playerList );
					cout << endl;
					break;

				case 3:
					playerList::tPlayerList sort = playerList::rankSort ( playerList );
					cout << endl;
					playerList::display ( sort );
					cout << endl;
					playerList::freeArray ( sort );
					break;

				case 4:
					sudokuList::registerSudoku ( sudokuList );
					break;

				case 0:
					sudokuList::save ( sudokuList );
					playerList::save ( playerList );
					playerList::freePlayers ( playerList );		// Free each dynamic tPlayer
					playerList::freeArray ( playerList );		// Free dynamic array of pointers
					break;
			}
		} while ( choice != 0 );
	}

	return 0;
}

int menu () {
	int choice;

	cout << "Menu:   " << "1. Play" << endl;
	cout << setw ( 8 ) << "" << "2. See players, sorted by ID" << endl;
	cout << setw ( 8 ) << "" << "3. See players, sorted by score" << endl;
	cout << setw ( 8 ) << "" << "4. Add sudoku" << endl;
	cout << setw ( 8 ) << "" << "0. Exit" << endl;

	do {
		cout << "Choice: ";
		cin >> choice;
	} while ( choice < 0 || choice > 4 );

	return choice;
}