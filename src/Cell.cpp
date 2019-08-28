#include "checkML.h"
#include "Cell.h"
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace cell;

void cell::initCell ( tCell& cell ) {
	cell.state = empty;
	fullSet ( cell.possible );
}

void cell::fillCell ( tCell& cell, char c, bool isFixed ) {
	if ( c == ' ' ) {
		cell.state = empty;
		cell.num = -1;
	}
	else if ( c >= '1' && c <= '9' ) {
		cell.num = c - '0';
		if ( isFixed ) {
			cell.state = fixed;
		}
		else {
			cell.state = filled;
		}
	}
}

void cell::bgColor ( int color ) {
	HANDLE handle = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute ( handle, 15 | (color << 4) );
}

void cell::drawCell ( const tCell & cell ) {
	switch ( cell.state ) {
		case fixed:
			bgColor ( 1 );
			cout << " " << cell.num << " ";
			break;
		case filled:
			bgColor ( 4 );
			cout << " " << cell.num << " ";
			break;
		case empty:
			cout << "   ";
			break;
	}
	bgColor ( 0 );
}

bool cell::isSimple ( const tCell & cell, int& number ) {
	bool simple = false;
	number = -1;
	if ( cell.state == empty ) {
		simple = one ( cell.possible, number );
	}
	return simple;
}
