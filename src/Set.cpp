#include "checkML.h"
#include "Set.h"
#include <iostream>

using namespace std;
using namespace set;

void set::emptySet ( tSet& set ) {
	for ( int i = 0; i < N; i++ ) {
		set.numArray[i] = false;
	}
	set.counter = 0;
}

void set::fullSet ( tSet& set ) {
	for ( int i = 0; i < N; i++ ) {
		set.numArray[i] = true;
	}
	set.counter = N;
}

bool set::isIn ( const tSet& set, int n ) {
	bool in = false;
	if ( n >= 1 && n <= N ) {
		in = set.numArray[n - 1];
	}
	return in;
}

void set::add ( tSet& set, int n ) {
	if ( n >= 1 && n <= N ) {
		if ( set.numArray[n - 1] == false ) {
			set.numArray[n - 1] = true;
			set.counter++;
		}
	}
}

void set::erase ( tSet& set, int n ) {
	if ( n >= 1 && n <= N ) {
		if ( set.numArray[n - 1] == true ) {
			set.numArray[n - 1] = false;
			set.counter--;
		}
	}
}

int set::size ( const tSet& set ) {
	return set.counter;
}

void set::display ( const tSet& set ) {
	cout << "[ ";
	for ( int i = 0; i < N; i++ ) {
		if ( set.numArray[i] ) {
			cout << i + 1 << " ";
		}
	}
	cout << "]";
}

bool set::one ( const tSet& set, int& n ) {
	bool oneElem;
	if ( size ( set ) == 1 ) {
		oneElem = true;
		n = findOne ( set );
	}
	else {
		oneElem = false;
		n = -1;
	}
	return oneElem;
}

int set::findOne ( const tSet& set ) {
	// assuming set has only 1 element
	bool found = false;
	int idx = 0;
	while ( !found && idx < N ) {
		if ( set.numArray[idx] == true ) {
			found = true;					// exit the loop and idx is the position in array of the elem
		}
		else {
			idx++;
		}
	}
	if ( !found ) {
		idx = -2;
	}
	return idx + 1;
}
