#include "checkML.h"
#include "PlayerList.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace playerList;

void playerList::create ( tPlayerList& list ) {
	list.players = new player::tPlayerPtr[INIT_SIZE];
	list.count = 0;
	list.size = INIT_SIZE;
}

bool playerList::load ( tPlayerList& list ) {
	bool ok = true;
	ifstream file;

	file.open ( fileName );
	if ( !file.is_open () ) {
		ok = false;
	}
	else {
		string aux;

		while ( file >> aux ) {
			if ( list.count == list.size ) {
				resize ( list );
			}
			list.players[list.count] = new player::tPlayer;
			list.players[list.count]->id = aux;
			file >> list.players[list.count]->score;
			list.count++;
		}

		file.close ();
	}

	return ok;
}

void playerList::display ( const tPlayerList& list ) {
	for ( int i = 0; i < list.count; i++ ) {
		cout << setw ( 20 ) << left << list.players[i]->id << list.players[i]->score << " pt(s)" << endl;
	}
}

bool playerList::save ( const tPlayerList& list ) {
	bool ok = true;
	ofstream file;

	file.open ( fileName );
	if ( !file.is_open () ) {
		ok = false;
	}
	else {
		for ( int i = 0; i < list.count; i++ ) {
			file << setw ( 12 ) << left << list.players[i]->id << setw ( 3 )
				<< right << list.players[i]->score << endl;
		}
		file.close ();
	}

	return ok;
}

void playerList::playerScore ( tPlayerList& list, int score ) {
	string id;
	int posInList;

	cout << "Player ID (one word): ";
	cin >> id;
	if ( find ( list, id, posInList ) ) {
		// Update score
		player::modifyPlayer ( *list.players[posInList], score );
	}
	else {
		// Add new player in position 'posInList' with that score
		if ( list.count == list.size ) {
			resize ( list );
		}
		addPlayer ( list, posInList, id, score );
	}
}

void playerList::addPlayer ( tPlayerList& list, int pos, string id, int score ) {

	if ( list.count == list.size ) {
		resize ( list );
	}
	for ( int i = list.count; i > pos; i-- ) {
		list.players[i] = list.players[i - 1];
	}
	list.players[pos] = new player::tPlayer;
	list.players[pos]->id = id;
	list.players[pos]->score = score;
	list.count++;
}

bool playerList::find ( const tPlayerList& list, std::string id, int& pos ) {
	bool found;

	pos = bSearch ( list, id, 0, list.count - 1 );
	if ( pos == -1 ) {
		found = false;
		// Not found, find pos where new player should be inserted:
		int idx = 0;
		bool finish = false;
		while ( idx < list.count && !finish ) {
			if ( list.players[idx]->id < id ) {
				idx++;
			}
			else {
				finish = true;
			}
		}
		pos = idx;
	}
	else {
		found = true;
	}

	return found;
}

int playerList::bSearch ( const  tPlayerList& list, std::string id, int beg, int end ) {
	int pos = -1, middle;

	if ( beg <= end ) {
		middle = (beg + end) / 2;
		if ( id == list.players[middle]->id ) {
			pos = middle;
		}
		else if ( id < list.players[middle]->id ) {
			pos = bSearch ( list, id, beg, middle - 1 );
		}
		else {
			pos = bSearch ( list, id, middle + 1, end );
		}
	}

	return pos;
}

tPlayerList playerList::rankSort ( const tPlayerList & list ) {
	tPlayerList sort;	// Sort is initially a copy of list and points to the same tPlayers

	sort.players = new player::tPlayerPtr[list.size];
	sort.count = list.count;
	sort.size = list.size;
	for ( int i = 0; i < list.count; i++ ) {
		sort.players[i] = list.players[i];
	}

	int highest;
	player::tPlayerPtr aux;

	for ( int i = 0; i < sort.count - 1; i++ ) {
		highest = i;
		for ( int j = i + 1; j < list.count; j++ ) {
			if ( sort.players[j]->score > sort.players[highest]->score ) {
				highest = j;
			}
		}
		if ( highest > i ) {
			aux = sort.players[i];
			sort.players[i] = sort.players[highest];
			sort.players[highest] = aux;
		}
	}
	// If an score matches another, sort them by ID in descending order	
	matchedScores ( sort );

	return sort;
}

void playerList::matchedScores ( tPlayerList & sort ) {
	bool matchFound = false;
	int beg, end;

	for ( int i = 0; i < sort.count - 1; i++ ) {
		if ( !matchFound && sort.players[i + 1]->score == sort.players[i]->score ) {
			beg = i;
			end = i + 1;
			matchFound = true;
		}
		else if ( matchFound && sort.players[i + 1]->score == sort.players[i]->score ) {
			// Several matches in a row
			end = i + 1;
		}
		else if ( matchFound && sort.players[i + 1]->score != sort.players[i]->score ) {
			// The matches' concatenation stops -> sort it
			sortById ( sort, beg, end );	// It sorts IDs in descending order (from z to a), so:
			reverseOrder ( sort, beg, end );
			matchFound = false;
		}

		if ( i == sort.count - 2 && matchFound ) {
			// When checking for a match with the last elem in list, there won't be more iterations 
			// of the loop, so if a match was found, it must be sorted inmediatly
			sortById ( sort, beg, end );	// It sorts IDs in descending order (from z to a), so:
			reverseOrder ( sort, beg, end );
			matchFound = false;
		}
	}
}

void playerList::sortById ( tPlayerList & sort, int beg, int end ) {
	int highest;
	player::tPlayerPtr aux;

	for ( int i = beg; i < end; i++ ) {
		highest = i;
		for ( int j = i + 1; j <= end; j++ ) {
			if ( sort.players[j]->id > sort.players[highest]->id ) {
				highest = j;
			}
		}
		if ( highest > i ) {
			aux = sort.players[i];
			sort.players[i] = sort.players[highest];
			sort.players[highest] = aux;
		}
	}
}

void playerList::reverseOrder ( tPlayerList & list, int beg, int end ) {
	int elemsToSwap = end - beg + 1;
	player::tPlayerPtr aux;

	for ( int i = 1; i <= (elemsToSwap / 2); i++ ) {
		aux = list.players[beg + i - 1];
		list.players[beg + i - 1] = list.players[beg + elemsToSwap - i];
		list.players[beg + elemsToSwap - i] = aux;
	}
}

void playerList::resize ( tPlayerList & list ) {
	tArrayPtr aux = new player::tPlayerPtr[list.size * 2];		//new dynamic array
	for ( int i = 0; i < list.count; i++ ) {					// Copy contents (address of each tPlayer)
		aux[i] = list.players[i];
	}
	delete[] list.players;			// Free small array (but not of its elements)
	list.players = aux;				// list.players pointing to the recently created bigger array
	list.size *= 2;
	// list.count is not affected
}

void playerList::freeArray ( tPlayerList & list ) {
	delete[] list.players;
}

void playerList::freePlayers ( tPlayerList & list ) {
	for ( int i = 0; i < list.count; i++ ) {
		delete list.players[i];
	}
}
