#include "checkML.h"
#include "Board.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace board;

void board::init ( tBoard board ) {
	for ( int row = 0; row < DIM; row++ ) {
		for ( int col = 0; col < DIM; col++ ) {
			initCell ( board[row][col] );
		}
	}
}

bool board::checkPos ( const tBoard board, int row, int col, int n ) {
	bool ok = false;
	if ( checkRow ( board, row, col, n ) ) {
		if ( checkCol ( board, row, col, n ) ) {
			if ( checkSubsquare ( board, row, col, n ) ) {
				ok = true;
			}
		}
	}
	return ok;
}

bool board::checkRow ( const tBoard board, int row, int col, int n ) {
	bool ok = true;
	for ( int i = 0; i < DIM; i++ ) {
		if ( board[row][i].num == n ) {
			ok = false;
		}
	}
	return ok;
}

bool board::checkCol ( const tBoard board, int row, int col, int n ) {
	bool ok = true;
	for ( int i = 0; i < DIM; i++ ) {
		if ( board[i][col].num == n ) {
			ok = false;
		}
	}
	return ok;
}

bool board::checkSubsquare ( const tBoard board, int row, int col, int n ) {
	bool ok = true;

	int iniRow, iniCol;		// They are the top-left position of the subSquare in which 'cell' is
	iniRow = row - (row % 3);
	iniCol = col - (col % 3);

	for ( int currRow = iniRow; currRow < iniRow + 3; currRow++ ) {
		for ( int currCol = iniCol; currCol < iniCol + 3; currCol++ ) {
			if ( board[currRow][currCol].num == n ) {
				ok = false;
			}
		}
	}

	return ok;
}

void board::updatePossibles ( tBoard board, int row, int col, int n, bool erase ) {
	updatePosRow ( board, row, n, erase );
	updatePosCol ( board, col, n, erase );
	updatePosSubSquare ( board, row, col, n, erase );
}

void board::updatePosRow ( tBoard board, int row, int n, bool erase ) {
	if ( erase ) {
		for ( int i = 0; i < DIM; i++ ) {
			set::erase ( board[row][i].possible, n );
		}
	}
	else {
		// Only add 'n' to possible values of a related cell if 
		// for that cell there's no related cells with that value
		for ( int i = 0; i < DIM; i++ ) {
			if ( checkPos ( board, row, i, n ) ) {
				set::add ( board[row][i].possible, n );
			}
		}
	}
}

void board::updatePosCol ( tBoard board, int col, int n, bool erase ) {
	if ( erase ) {
		for ( int i = 0; i < DIM; i++ ) {
			set::erase ( board[i][col].possible, n );
		}
	}
	else {
		// Only add 'n' to possible values of a related cell if 
		// for that cell there's no related cells with that value
		for ( int i = 0; i < DIM; i++ ) {
			if ( checkPos ( board, i, col, n ) ) {
				set::add ( board[i][col].possible, n );
			}
		}
	}
}

void board::updatePosSubSquare ( tBoard board, int row, int col, int n, bool erase ) {
	int iniRow, iniCol;		// They are the top-left position of the subSquare in which 'cell' is
	iniRow = row - (row % 3);
	iniCol = col - (col % 3);

	if ( erase ) {
		for ( int currRow = iniRow; currRow < iniRow + 3; currRow++ ) {
			for ( int currCol = iniCol; currCol < iniCol + 3; currCol++ ) {
				set::erase ( board[currRow][currCol].possible, n );
			}
		}
	}
	else {
		// Only add 'n' to possible values of a related cell if 
		// for that cell there's no related cells with that value
		for ( int currRow = iniRow; currRow < iniRow + 3; currRow++ ) {
			for ( int currCol = iniCol; currCol < iniCol + 3; currCol++ ) {
				if ( checkPos ( board, currRow, currCol, n ) ) {
					set::add ( board[currRow][currCol].possible, n );
				}
			}
		}
	}
}

bool board::load ( const string& filename, tBoard board ) {
	bool ok = true;
	char ch;
	ifstream file;
	string str;

	file.open ( filename );
	if ( !file.is_open () ) {
		ok = false;
	}
	else {
		for ( int row = 0; row < DIM; row++ ) {
			getline ( file, str );
			for ( int col = 0; col < DIM; col++ ) {
				ch = str.at ( col );
				fillCell ( board[row][col], ch, true );
				if ( ch >= '1' && ch <= '9' ) {
					updatePossibles ( board, row, col, ch - '0' );
				}
			}
		}
		file.close ();
	}

	return ok;
}

void board::draw ( const tBoard board ) {
	int ROWS = DIM;
	int COLUMNS = DIM;

	// Top line
	cout << endl << " " << char ( 218 );
	for ( int col = 0; col < COLUMNS - 1; col++ ) {
		cout << char ( 196 ) << char ( 196 ) << char ( 196 ) << char ( 194 );
	}
	cout << char ( 196 ) << char ( 196 ) << char ( 196 ) << char ( 191 ) << endl;

	// Body
	for ( int i = ROWS - 1; i >= 0; i-- ) {
		cout << ROWS - i;
		for ( int j = 0; j < COLUMNS; j++ ) {
			cout << char ( 179 );
			drawCell ( board[ROWS - 1 - i][j] );
		}
		cout << char ( 179 ) << endl;
		if ( i > 0 ) {
			cout << " " << char ( 195 );
			for ( int j = 0; j < COLUMNS - 1; j++ ) {
				cout << char ( 196 ) << char ( 196 ) << char ( 196 ) << char ( 197 );
			}
			cout << char ( 196 ) << char ( 196 ) << char ( 196 ) << char ( 180 ) << endl;
		}
		//Bottom Line
		else {
			cout << " " << char ( 192 );
			for ( int j = 0; j < COLUMNS - 1; j++ ) {
				cout << char ( 196 ) << char ( 196 ) << char ( 196 ) << char ( 193 );
			}
			cout << char ( 196 ) << char ( 196 ) << char ( 196 ) << char ( 217 ) << endl;
		}
	}
	cout << "  ";
	for ( int i = 1; i <= COLUMNS; i++ ) {
		cout << " " << i << "  ";
	}
	cout << endl << endl;
}

bool board::place ( tBoard board, int row, int col, int c ) {
	bool ok = false;
	if ( board[row][col].state == cell::empty && isIn ( board[row][col].possible, c ) ) {
		ok = true;
		fillCell ( board[row][col], c + '0' );
		updatePossibles ( board, row, col, c );
	}
	return ok;
}

bool board::erase ( tBoard board, int row, int col ) {
	bool ok = false;
	int value = board[row][col].num;
	if ( board[row][col].state == cell::filled ) {
		ok = true;
		fillCell ( board[row][col], ' ' );
		updatePossibles ( board, row, col, value, false );
	}
	return ok;
}

bool board::full ( const tBoard board ) {
	bool isFull = true;
	for ( int row = 0; row < DIM; row++ ) {
		for ( int col = 0; col < DIM; col++ ) {
			if ( board[row][col].state == cell::empty ) {
				isFull = false;
			}
		}
	}
	return isFull;
}

void board::possible ( const tBoard board, int row, int col ) {
	display ( board[row][col].possible );
}

void board::fillSimple ( tBoard board ) {
	int value;
	for ( int row = 0; row < DIM; row++ ) {
		for ( int col = 0; col < DIM; col++ ) {
			if ( one ( board[row][col].possible, value ) ) {
				place ( board, row, col, value );
			}
		}
	}
}
