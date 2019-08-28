#include "checkML.h"
#include "SudokuList.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace sudokuList;

void sudokuList::createList ( tSudokuList& list ) {
	list.counter = 0;
}

bool sudokuList::load ( tSudokuList& list ) {
	bool ok = true;
	string aux;
	ifstream file;

	file.open ( sudokuListFile );
	if ( !file.is_open () ) {
		ok = false;
	}
	else {
		createList ( list );
		file >> aux;
		while ( !file.eof () && list.counter < MAX_SUDOKUS ) {
			list.sudokuArray[list.counter].filename = aux;
			file >> list.sudokuArray[list.counter].score;
			list.counter++;
			file >> aux;
		}
		file.close ();
	}

	return ok;
}

void sudokuList::display ( const tSudokuList& list ) {
	cout << "Available Sudokus:  ";
	for ( int i = 0; i < list.counter; i++ ) {
		if ( i > 0 ) {
			cout << setw ( 20 ) << "";
		}
		cout << i + 1 << ". " << setw ( 20 ) << left
			<< list.sudokuArray[i].filename.substr ( 0, list.sudokuArray[i].filename.size () - 4 ) // avoid the .txt
			<< list.sudokuArray[i].score << " pts" << endl;
	}
}

game::tSudoku sudokuList::sudokuListMenu ( const tSudokuList & list ) {
	int choice;
	game::tSudoku chosenSudoku;

	display ( list );
	do {
		cout << "Choice (1 - " << list.counter << "): ";
		cin >> choice;
	} while ( choice < 1 || choice > list.counter );

	return list.sudokuArray[choice - 1];
}

bool sudokuList::save ( const tSudokuList & list ) {
	bool ok = true;
	ofstream file;

	file.open ( sudokuListFile );
	if ( !file.is_open () ) {
		ok = false;
	}
	else {
		for ( int i = 0; i < list.counter; i++ ) {
			file << list.sudokuArray[i].filename << " " << list.sudokuArray[i].score << endl;
		}
		file.close ();
	}

	return ok;
}

bool sudokuList::registerSudoku ( tSudokuList & list ) {
	bool ok = true;

	if ( list.counter >= MAX_SUDOKUS ) {
		ok = false;
		cout << "New sudoku can't be added (the list is full, no enough room for a new one)" << endl;
	}
	else {
		game::tSudoku newSdk;
		int pos;

		cout << "Sudoku's filename (include the .txt): ";
		cin >> newSdk.filename;
		while ( findFile ( list, newSdk.filename ) ) {
			cout << "This filename is already in use" << endl;
			cout << "Sudoku's filename (include the .txt): ";
			cin >> newSdk.filename;
		}

		cout << "Sudoku's score: ";
		cin >> newSdk.score;
		while ( newSdk.score < 0 ) {
			cout << "Invalid score..." << endl;
			cout << "Sudoku's score: ";
			cin >> newSdk.score;
		}

		pos = findPosition ( list, newSdk );
		insert ( list, newSdk, pos );
	}

	return ok;
}

void sudokuList::insert ( tSudokuList & list, const game::tSudoku & sudoku, int pos ) {
	if ( list.counter < MAX_SUDOKUS ) {
		for ( int i = list.counter; i > pos; i-- ) {
			list.sudokuArray[i] = list.sudokuArray[i - 1];
		}
		list.sudokuArray[pos] = sudoku;
		list.counter++;
	}
}

bool sudokuList::findFile ( const tSudokuList & list, const string & filename ) {
	bool found = false;
	int i = 0;
	while ( !found && i < list.counter ) {
		if ( list.sudokuArray[i].filename == filename ) {
			found = true;
		}
		i++;
	}
	return found;
}

int sudokuList::findPosition ( const tSudokuList & list, const game::tSudoku & sudoku ) {
	return binarySearchPosition ( list.sudokuArray, sudoku, 0, list.counter - 1 );
}

int sudokuList::binarySearchPosition ( const tSudokuArray & list, const game::tSudoku & sudoku, int beg, int end ) {
	// The ascending comparison is: (score1 < score2) || (score1 == score2 && filename1 < filename2)

	int pos = -1, middlePos;
	game::tSudoku middle;

	if ( beg <= end ) {
		middlePos = (beg + end) / 2;
		middle = list[middlePos];

		if ( sudoku.score == middle.score && sudoku.filename == middle.filename ) {
			// The new sudoku is already in the list -> don't insert it
			pos = -1;
		}
		else if ( (sudoku.score < middle.score) ||
			(sudoku.score == middle.score && sudoku.filename < middle.filename) ) {
			pos = binarySearchPosition ( list, sudoku, beg, middlePos - 1 );
		}
		else {
			pos = binarySearchPosition ( list, sudoku, middlePos + 1, end );
		}

	}
	else {
		// If not found (beg > end):
		if ( (sudoku.score < list[end].score) ||
			(sudoku.score == list[end].score && sudoku.filename < list[end].filename) ) {
			pos = end;
		}
		else {
			pos = beg;
		}
	}

	return pos;
}
